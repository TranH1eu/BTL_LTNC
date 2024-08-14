

#include "main.h"
#include "commonFunction.h"
#include "baseFunction.h"
#include "mainMap.h"
#include "mainObject.h"
#include "Timer.h"
#include "threatsObj.h"
#include "explosionObj.h"
#include "textDisplay.h"
#include "Blood.h"
#include "bossThreat.h"


baseFunction g_background;
TTF_Font* fontTime = NULL;


bool InitData() {

	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if(ret < 0 ) return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("Final Game",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH, SCREEN_HIGHT,
								SDL_WINDOW_SHOWN);
	if (g_window ==NULL) {
		success = false;

	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if(g_screen == NULL)success = false;
		else {
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags)&& imgFlags)) success = false;
		}
		if(TTF_Init() == -1) {
			success = false;
		}

		fontTime = TTF_OpenFont("font//font.ttf", 15);
		if(fontTime == NULL) {
			success = false;
		}
	}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		return false;
	}
	g_sound_bullet[0] = Mix_LoadWAV("sound//laserGun.wav");
	g_sound_bullet[1] = Mix_LoadWAV("sound//Gun1.wav");

	g_sound_exp[0] = Mix_LoadWAV("sound//Explosion.wav");
	g_sound_exp[1] = Mix_LoadWAV("sound//die.wav");
	if(g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL) return false;
	return success;
}


bool LoadBackground() {

	bool ret = g_background.LoadImg("img//blue.png", g_screen);
	if(ret == false) return false;
	return true;
}

void close() {
	g_background;
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

void InitThreatsAndBullets(SDL_Renderer* screen, threatsObj& threat) {
    // Initialize threat
    threat.InitThreats();
    threat.set_clips();
    threat.setMapXY(0, 0);
    threat.set_type_move(threatsObj::MOVE_IN_SPACE_THREAT);
    threat.setAnimationPos(0, 400);
    threat.set_input_left(1);

    // Initialize bullets
    bulletObj* bullet1 = new bulletObj();
    threat.InitBullet(bullet1, screen, bulletObj::DIR_LEFT);

    bulletObj* bullet2 = new bulletObj();
    threat.InitBullet(bullet2, screen, bulletObj::DIR_RIGHT);
}

std::vector<threatsObj*> MakeThreatList() {

	std::vector<threatsObj*> list_threats;



	threatsObj* dynamic_threats = new threatsObj[25];
	for(int i=0;i<25;i++) {
		threatsObj* p_threat = (dynamic_threats+i);
		if(p_threat != NULL) {
			p_threat->LoadImg("img//threat_level.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(threatsObj::MOVE_IN_SPACE_THREAT);
			p_threat->set_x_pos(500+i*1000);
			p_threat->set_y_pos(100);

			int pos1 = p_threat->get_x_pos() - 60;
			int pos2 = p_threat->get_x_pos() + 60;
			p_threat->setAnimationPos(pos1, pos2);

			p_threat->set_type_move(threatsObj::MOVE_IN_SPACE_THREAT);
			bulletObj* p_bullet = new bulletObj();

			if(p_threat->isMovingLeft()) {
				p_threat->InitBullet(p_bullet, g_screen, bulletObj::DIR_RIGHT);
			}
			else if(p_threat->isMovingRight()) {
				p_threat->InitBullet(p_bullet, g_screen, bulletObj::DIR_LEFT);
			}

			list_threats.push_back(p_threat);
		}
	}

	threatsObj* threats_num = new threatsObj[20];

	for(int i=0;i<20;i++) {
		threatsObj* p_threat = (threats_num+i);
		if(p_threat != NULL) {
			p_threat->LoadImg("img//static.png", g_screen);
			p_threat->set_clips();
			p_threat->set_x_pos(700 + i*1200);
			p_threat->set_y_pos(250);

			p_threat->set_type_move(threatsObj::STATIC_THREAT);
			p_threat->set_input_left(0);
			list_threats.push_back(p_threat);


		}
	}



	return list_threats;
}


int main(int argc, char* argv[])
{

	Timer fps_timer;

	if(InitData() == false)
		return -1;
	if(LoadBackground() == false)
		return -1;

	mainMap gameMap;

	gameMap.LoadMap("map//map01.dat");


	gameMap.LoadTiles(g_screen);

	mainObject p_player;
	p_player.LoadImg("img//soldier_right.png", g_screen);
	p_player.set_clips();

	threatsObj threat;
    InitThreatsAndBullets(g_screen, threat);

	std::vector<threatsObj*> threats_list = MakeThreatList();

	//boss threat
	bossThreat bossObj;
	bossObj.LoadImg("img//bossThreat.png", g_screen);
	bossObj.set_clips();
	int xPos = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6;
	bossObj.set_xpos(xPos);
	bossObj.set_ypos(10);
	int cnt =0;



	explosionObj exp_threat;
	bool tRect = exp_threat.LoadImg("img//explosion.png", g_screen);
	if(!tRect) return -1;
	exp_threat.set_clip();

	Blood player_blood;
	player_blood.Init(g_screen);

	int cnt_die = 0;

	//Time text
	textDisplay time_game;
	time_game.setColor(textDisplay::WHITE_TEXT);

	textDisplay mark;
	mark.setColor(textDisplay::WHITE_TEXT);
	UINT mark_value = 0;

	textDisplay money_game;
	money_game.setColor(textDisplay::WHITE_TEXT);



	bool is_quit = false;
	while(!is_quit) {
			fps_timer.start();

			while(SDL_PollEvent(&g_event) != 0) {
			if(g_event.type == SDL_QUIT) {
				is_quit = true;
			}

			p_player.HandleInputAction(g_event, g_screen, g_sound_bullet);

		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		player_blood.Show(g_screen);

		Map map_data = gameMap.getMap();

		p_player.HandleBullet(g_screen);
		p_player.setMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);
		if(p_player.Fall() == true) {
			player_blood.Decrease();
			player_blood.Render(g_screen);

		}
		if(p_player.getOutOfPlayer()+cnt_die>3) {
				if(MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {

							close();
							SDL_Quit();
							return 0;
					}

		}




		gameMap.setMap(map_data);
		gameMap.DrawMap(g_screen);



		for(int i=0;i<threats_list.size();i++) {
			threatsObj* p_threat = threats_list.at(i);

			if(p_threat != NULL) {
				p_threat->setMapXY(map_data.start_x_, map_data.start_y_);
				p_threat->ImpMoveType(g_screen);
				p_threat->DoPlayer(map_data);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HIGHT);
				p_threat->Show(g_screen);

				SDL_Rect rect_player = p_player.GetRectFrame();
				bool bColl1 = false;
				std::vector<bulletObj*> tBullet_list = p_threat->get_bullet_list();
				for(int j =0;j<tBullet_list.size();j++) {
					bulletObj* pt_bullet = tBullet_list.at(j);
					if(pt_bullet) {
						bColl1 = SDLCommonFunc::collisionCheck(pt_bullet->GetRect(), rect_player);
						if(bColl1 == true && cnt_die > 2) {
							p_threat->RemoveBullet(j);
							break;
						}
					}
				}

				SDL_Rect rect_threat = p_threat->GetRectFrame();

				bool bColl2 = SDLCommonFunc::collisionCheck(rect_player, rect_threat);
				if(bColl1 || bColl2) {
					Mix_PlayChannel(-1, g_sound_exp[1], 0);

					int frame_exp_width = exp_threat.get_frame_width();
					int frame_exp_height = exp_threat.get_frame_height();

					for(int ex =0;ex<4;ex++) {
						int x_pos = (p_player.GetRect().x + p_player.get_width_frame()*0.5) - frame_exp_width*0.5;
						int y_pos = (p_player.GetRect().y + p_player.get_height_frame()*0.5)- frame_exp_height*0.5;
						exp_threat.set_frame(ex);
						exp_threat.SetRect(x_pos, y_pos);
						exp_threat.Show(g_screen);
					}

					cnt_die++;
					if(cnt_die<=3 || p_player.Fall()) {

						p_player.SetRect(0, 0);
						p_player.set_comback_time(1);
						player_blood.Decrease();
						player_blood.Render(g_screen);
						continue;
					}

					else {
						if(MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
							p_threat->Free();

							close();
							SDL_Quit();
							return 0;
						}

					}



				}


			}
		}
		int frame_exp_width = exp_threat.get_frame_width();
		int frame_exp_height = exp_threat.get_frame_height();



		std::vector<bulletObj*> bullet_arr = p_player.get_bullet_list();
		for (int r =0;r<bullet_arr.size();r++) {
			bulletObj* p_bullet = bullet_arr.at(r);
			if(p_bullet != NULL) {
				for(int t=0;t<threats_list.size();t++) {
					threatsObj* obj_threat = threats_list.at(t);
					if(obj_threat!=NULL) {
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();
						bool bColl = SDLCommonFunc::collisionCheck(bRect, tRect);
						if(bColl) {


							for(int ex =0;ex<NUM_FRAME_EXP;ex++) {
								int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
								int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
							}

							p_player.RemoveBullet(r);
							if(obj_threat->isDynamic()) {
								obj_threat->Free();
								threats_list.erase(threats_list.begin() + t);
								Mix_PlayChannel(-1, g_sound_exp[0], 0);
								mark_value++;
							}
							else if(!obj_threat->isDynamic()) {
								p_player.RemoveBullet(r);
								Mix_PlayChannel(-1, g_sound_exp[0], 0);
								/*obj_threat->IncreaseHitCount();
								if(obj_threat->GetHitCount() >= 3) {
									obj_threat->Free();
									threats_list.erase(threats_list.begin() + t);
								}*/


							}
							//obj_threat->Free();
							//threats_list.erase(threats_list.begin() + t);

						}

					}
				}
			}
		}



		//Show game time
		std::string str_time = "TIME: ";
		Uint32 time_val = SDL_GetTicks()/1000;
		Uint32 val_time= 180 - time_val;
		if(val_time<=0) {
			if(MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {

				is_quit = true;
				break;
			}
		}
		else {

			std::string str_val  = std::to_string(val_time);
			str_time += str_val;
			time_game.setText(str_time);
			time_game.LoadFromRenderText(fontTime, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
		}

		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark = "KILL: ";
		strMark += val_str_mark;
		mark.setText(strMark);
		mark.LoadFromRenderText(fontTime, g_screen);
		mark.RenderText(g_screen, SCREEN_WIDTH - 600, 15);


		int money_cnt = p_player.getCountMoney();
		std::string money_str = std::to_string(money_cnt);
		std::string strCoin = "COIN: ";
		strCoin += money_str;
		money_game.setText(strCoin);
		money_game.LoadFromRenderText(fontTime, g_screen);
		money_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);

		//show bos
		int val = MAX_MAP_X*TILE_SIZE - (map_data.start_x_ + p_player.GetRect().x);\
		if(val <= SCREEN_WIDTH ){


			bossObj.SetMapXY(map_data.start_x_, map_data.start_y_);
			bossObj.DoPlayer(map_data);
			bossObj.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HIGHT);
			bossObj.Show(g_screen);
			SDL_Rect rect_player = p_player.GetRectFrame();
				bool bColl1 = false;
				std::vector<bulletObj*> tBullet_list = bossObj.get_bullet_list();
				for(int j =0;j<tBullet_list.size();j++) {
					bulletObj* pt_bullet = tBullet_list.at(j);
					if(pt_bullet) {
						bColl1 = SDLCommonFunc::collisionCheck(pt_bullet->GetRect(), rect_player);
						if(bColl1 == true && cnt_die > 2) {
							bossObj.RemoveBullet(j);
							break;
						}
					}
				}

				SDL_Rect rect_boss_threat = bossObj.GetRectFrame();

				bool bColl2 = SDLCommonFunc::collisionCheck(rect_player, rect_boss_threat);
				if(bColl1 || bColl2) {
					Mix_PlayChannel(-1, g_sound_exp[1], 0);

					int frame_exp_width = exp_threat.get_frame_width();
					int frame_exp_height = exp_threat.get_frame_height();

					for(int ex =0;ex<4;ex++) {
						int x_pos = (p_player.GetRect().x + p_player.get_width_frame()*0.5) - frame_exp_width*0.5;
						int y_pos = (p_player.GetRect().y + p_player.get_height_frame()*0.5)- frame_exp_height*0.5;
						exp_threat.set_frame(ex);
						exp_threat.SetRect(x_pos, y_pos);
						exp_threat.Show(g_screen);
					}

					cnt_die++;
					if(cnt_die<=3 || p_player.Fall()) {

						p_player.SetRect(0, 0);
						p_player.set_comback_time(1);
						player_blood.Decrease();
						player_blood.Render(g_screen);
						continue;
					}

					else {
						if(MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
							bossObj.Free();

							close();
							SDL_Quit();
							return 0;
						}

					}
				}


				for (int r =0;r<bullet_arr.size();r++) {
					bulletObj* p_bullet = bullet_arr.at(r);
					if(p_bullet != NULL) {



								SDL_Rect tRect1;
								tRect1.x = bossObj.GetRect().x;
								tRect1.y = bossObj.GetRect().y;
								tRect1.w = bossObj.get_width_frame();
								tRect1.h = bossObj.get_height_frame();

								SDL_Rect bRect1 = p_bullet->GetRect();
								bool bColl = SDLCommonFunc::collisionCheck(bRect1, tRect1);

								if(bColl) {


									for(int ex =0;ex<NUM_FRAME_EXP;ex++) {
										int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
										int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

										exp_threat.set_frame(ex);
										exp_threat.SetRect(x_pos, y_pos);
										exp_threat.Show(g_screen);
									}
									cnt++;
									p_player.RemoveBullet(r);
									Mix_PlayChannel(-1, g_sound_exp[0], 0);





							}
							if(cnt>3) {

								if(MessageBoxW(NULL, L"U WIN", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
									bossObj.Free();

									close();
									SDL_Quit();
									return 0;
						}

							}
							//obj_threat->Free();
							//threats_list.erase(threats_list.begin() + t);

						}



			}
		}














		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks();
		int timePerFrame = 700/FRAME_PER_SECOND;
		if(real_imp_time < timePerFrame) {

			int delay_time = timePerFrame - real_imp_time;
			if(delay_time >=0 )
				SDL_Delay(delay_time);
		}
	}
	close();
    return 0;
}


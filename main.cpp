

#include "main.h"
#include "commonFunction.h"
#include "baseFunction.h"
#include "mainMap.h"
#include "mainObject.h"
#include "Timer.h"
#include "threatsObj.h"

baseFunction g_background;


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
	}

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

			list_threats.push_back(p_threat);
		}
	}

	threatsObj* threats_num = new threatsObj[20];

	for(int i=0;i<20;i++) {
		threatsObj* p_threat = (threats_num+i);
		if(p_threat != NULL) {
			p_threat->LoadImg("img//threat_test.png", g_screen);
			p_threat->set_clips();
			p_threat->set_x_pos(700 + i*1200);
			p_threat->set_y_pos(250);

			p_threat->set_type_move(threatsObj::STATIC_THREAT);
			p_threat->set_input_left(0);
			bulletObj* p_bullet = new bulletObj();
			p_threat->InitBullet(p_bullet, g_screen);
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

	std::vector<threatsObj*> threats_list = MakeThreatList();


	bool is_quit = false;
	while(!is_quit) {
			fps_timer.start();

			while(SDL_PollEvent(&g_event) != 0) {
			if(g_event.type == SDL_QUIT) {
				is_quit = true;
			}

			p_player.HandleInputAction(g_event, g_screen);

		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);


		Map map_data = gameMap.getMap();

		p_player.HandleBullet(g_screen);
		p_player.setMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);



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




#include "main.h"
#include "commonFunction.h"
#include "baseFunction.h"
#include "mainMap.h"
#include "mainObject.h"
#include "Timer.h"

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


int main(int argc, char* argv[])
{
	Timer fps_timer;

	if(InitData() == false)
		return -1;
	if(LoadBackground() == false)
		return -1;

	mainMap gameMap;

	gameMap.LoadMap("map/map01.dat");


	gameMap.LoadTiles(g_screen);

	mainObject p_player;
	p_player.LoadImg("img/soldier_right.png", g_screen);
	p_player.set_clips();

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


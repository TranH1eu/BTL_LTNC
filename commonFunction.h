
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<windows.h>
#include<string>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include "textDisplay.h"
#include "baseFunction.h"



static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Renderer* g_menu = NULL;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];


static SDL_Renderer* g_img_menu = NULL;

//man hinh
const int FRAME_PER_SECOND = 25;//fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HIGHT = 640;
const int SCREEN_PIXEL = 32;

const int COLOR_KEY_R = 49;
const int COLOR_KEY_G = 27;
const int COLOR_KEY_B = 32;

const int RENDER_DRAW_COLOR = 0xff;


#define BLANK_SIZE 0

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4

typedef struct Input {

	int left_;
	int right_;
	int up_;
	int down_;
	int run_;
};

typedef struct Map {

	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};


namespace SDLCommonFunc{
	static SDL_Texture* p_object_;
	static SDL_Rect rect_;

	bool LoadImg(std::string path, SDL_Renderer* screen);
	bool collisionCheck(const SDL_Rect& object1, const SDL_Rect& object2);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

	int showMenu(SDL_Renderer* des, TTF_Font* font);
	bool checkFocusWithRect(const int& x, const int& y,const SDL_Rect& rect);


}

#endif // COMMMON_FUNCTION_H_

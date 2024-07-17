
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "commonFunction.h"
#include "baseFunction.h"

#define MAX_TILES 30

class TileMap : public baseFunction{

public:
	TileMap() {;}
	~TileMap() {;}

};

class mainMap {

public:
	mainMap() {;}
	~mainMap() {;}

	void LoadMap(char* name);
	void LoadNewMap(char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const {return game_map_;};
	void setMap(Map map_data) {game_map_ = map_data;};

private:
	Map game_map_;
	TileMap tile_map[MAX_TILES];
};

#endif // GAME_MAP_H

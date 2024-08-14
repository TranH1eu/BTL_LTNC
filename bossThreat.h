
#ifndef BOSS_THREAT_H_
#define BOSS_THREAT_H_

#include "main.h"
#include "commonFunction.h"
#include "bulletObj.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10

#define PLAYER_SPEED 2
#define PLAYER_JUMP_VAL 18

#define FRAME_NUM_32 32

class bossThreat : public baseFunction {

public :

	bossThreat();
	~bossThreat();

	void set_x_val(int xp) {x_val_ = xp;}
	void set_y_val(int yp) {y_val_ = yp;}

	void set_xpos(const int& xpos) {x_pos_ = xpos;}
	void set_ypos(const int& ypos) {y_pos_ = ypos;}
	int get_xpos() {return x_pos_;}
	int get_ypos() {return y_pos_;}

	void Show(SDL_Renderer* des);
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void set_clips();

	int get_width_frame() const {return width_frame_;}
	int get_height_frame() const {return height_frame_;}

	void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;};

	void DoPlayer(Map& gMap);
	void InitPlayer();
	std::vector<bulletObj*> get_bullet_list() const {return bullet_list_;}
	void set_bullet_list(const std::vector<bulletObj*>& am_list) {bullet_list_ = am_list;}

	void InitBullet(SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);
private:
	int map_x_;
	int map_y_;
	int on_ground_;
	int think_time_;
	int frame_;
	SDL_Rect frame_clip[FRAME_NUM_32];
	int x_pos_;
	int y_pos_;
	int x_val_;
	int y_val_;
	int width_frame_;
	int height_frame_;
	std:vector<bulletObj*> bullet_list_;

};

#endif // BOSS_THREAT_H_

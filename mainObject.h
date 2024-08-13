
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>

#include "commonFunction.h"
#include "baseFunction.h"
#include "bulletObj.h"


#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 18
class mainObject : public baseFunction {
public:
	mainObject();
	~mainObject();

	enum WalkType {
		WALK_RIGHT=0,
		WALK_LEFT= 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
	};

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[2]);
	void set_clips();

	void DoPlayer(Map& map_data);
	void checkMap(Map& map_data);

	int get_width_frame() const {return width_frame_;}
	int get_height_frame() const {return height_frame_;}

	void set_y_pos(const float& yPos) {y_pos_ = yPos;}
	float get_y_pos() const {return y_pos_;}



	void setMapXY(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}
	void CenterEntityOnMap(Map& map_data);
	SDL_Rect GetRectFrame();

	void set_bullet_list(std::vector<bulletObj*> bullet_list) {

		p_bullet_list_ = bullet_list;

	}
	std::vector<bulletObj*> get_bullet_list() const {return p_bullet_list_;}

	void HandleBullet(SDL_Renderer* des);

	void IncreaseMoney();

	void RemoveBullet(const int& idex);

	void set_comback_time(const int& cb_time) {	comeback_time_ = cb_time;}

	int getOutOfPlayer() const{return cnt_fall;}

	int getCountMoney() const{return money_cnt;}

	int Fall() {return fall_;}


private:

	int money_cnt = 0;

	std::vector<bulletObj*> p_bullet_list_;

	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];

	Input input_type_;
	int frame_;
	int	status_;
	int last_status_;

	bool onGround;

	int map_x_;
	int map_y_;

	int comeback_time_;

	int cnt_fall;

	int fall_;

};

#endif // MAIN_OBJECT_H_

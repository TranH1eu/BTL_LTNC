
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_


#include "commonFunction.h"
#include "baseFunction.h"

#define MAX_THREAT_FALL_SPEED 10
#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_SPEED 3

class threatsObj : public baseFunction {

public :
	threatsObj();
	~threatsObj();

	enum TypeMove {

		STATIC_THREAT =0,
		MOVE_IN_SPACE_THREAT = 1,
	};

	void set_x_val(const float& xVal) {x_val_ = xVal;}
	void set_y_val(const float& yVal) {y_val_ = yVal;}

	void set_x_pos(const float& xPos) {x_pos_ = xPos;}
	void set_y_pos(const float& yPos) {y_pos_ = yPos;}
	float get_y_pos() const {return y_pos_;}
	float get_x_pos() const {return x_pos_;}

	void setMapXY(const int& mp_x, const int& mp_y) {map_x_ = mp_x; map_y_ = mp_y;}

	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int get_width_frame() const {return width_frame_;}
	int get_height_frame() const {return height_frame_;}
	void DoPlayer(Map& gMap);
	void checkMap(Map& gMap);

	void InitThreats();
	void set_type_move(const int& typeMove) {type_move_ = typeMove;}
	void setAnimationPos(const int& pos_a, const int& pos_b) {animation_a_ = pos_a, animation_b_ = pos_b;}
	void set_input_left(const int& ipleft) {input_type_.left_ = ipleft;};
	void ImpMoveType(SDL_Renderer* screen);


private :

	int map_x_;
	int map_y_;

	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;

	bool on_ground;
	int comeback_time;

	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;

	int type_move_;
	int animation_a_;
	int animation_b_;
	Input input_type_;

};

#endif // THREATS_OBJECT_H_

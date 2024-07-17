
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonFunction.h"
#include "baseFunction.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 20

class mainObject : public baseFunction {
public:
	mainObject();
	~mainObject();

	enum WalkType {
		WALK_RIGHT=0,
		WALK_LEFT= 1,
	};

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	void DoPlayer(Map& map_data);
	void checkMap(Map& map_data);


	void setMapXY(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}
	void CenterEntityOnMap(Map& map_data);


private:
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

	bool onGround;

	int map_x_;
	int map_y_;

	int comeback_time_;



};

#endif // MAIN_OBJECT_H_

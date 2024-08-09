
#include "main.h"
#include "bulletObj.h"

bulletObj::bulletObj() {

	x_val_ =0;
	y_val_ =0;
	is_move_=0;
	bullet_type_ = SPHERE_BULLET;

}

bulletObj::~bulletObj() {

}

void bulletObj::LoadImgBullet(SDL_Renderer* des) {

	if(bullet_type_ == SPHERE_BULLET){
		LoadImg("img//gun.png", des);
	}
	if(bullet_type_ == LASER_BULLET) {
		LoadImg("img//water_bullet.png", des);
	}
}

void bulletObj::HandleMove(const int& x_border, const int& y_border) {



	if(bullet_dir_ == DIR_RIGHT) {
		rect_.x += x_val_;
		if(rect_.x>x_border) {
			is_move_ = false;

		}
	}
	else if(bullet_dir_ == DIR_LEFT) {
		rect_.x-= x_val_;
		if(rect_.x<0) {
			is_move_ = false;

		}
	}
	else if(bullet_dir_ == DIR_DOWN) {
		rect_.y += y_val_;
		if(rect_.y > y_border){
			is_move_ = false;
		}
	}
	else if(bullet_dir_ == DIR_UP) {
		rect_.y -= y_val_;
		if(rect_.y < 0) {
			is_move_ = false;
		}
	}
	else if(bullet_dir_ == DIR_UPLEFT) {
		rect_.x -=x_val_;
		if(rect_.x < 0) {
			is_move_ = false;
		}
		rect_.y -=y_val_;
		if(rect_.y < 0) is_move_ = false;
	}
	else if(bullet_dir_ == DIR_UPRIGHT) {
		rect_.x +=x_val_;
		if(rect_.x > x_border) {
			is_move_ = false;
		}
		rect_.y -=y_val_;
		if(rect_.y < 0) is_move_ = false;
	}



}

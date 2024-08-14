#include "main.h"
#include "bossThreat.h"

bossThreat::bossThreat() {
	frame_ =0;
	x_val_=0.0;
	y_val_=0.0;
	x_pos_ =0;
	y_pos_=0;
	width_frame_ =0;
	height_frame_ =0;
	think_time_ =0;
	map_x_=0;
	map_y_=0;



}

bossThreat::~bossThreat() {}

bool bossThreat::LoadImg(std::string path, SDL_Renderer* screen) {

	bool ret = baseFunction::LoadImg(path, screen);

	if(ret == true) {
		width_frame_ = rect_.w/FRAME_NUM_32;
		height_frame_ = rect_.h;

	}
	return ret;
}

SDL_Rect bossThreat::GetRectFrame() {

	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}

void bossThreat::set_clips() {

	if(width_frame_>0 && height_frame_ > 0) {

		for(int i=0;i<FRAME_NUM_32;i++) {

			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void bossThreat::Show(SDL_Renderer* des) {

	if(think_time_ == 0) {
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if(frame_>=32) {
			frame_ =0;
		}

		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

		if(currentClip != NULL) {
			renderQuad.w = currentClip->w;
			renderQuad.h = currentClip->h;
		}

		SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);

	}
}

void bossThreat::DoPlayer(Map& gMap) {

	if(think_time_== 0) {
		x_val_ =0;
		y_val_ += THREAT_GRAVITY_SPEED;
		if(y_val_ >= MAX_THREAT_FALL_SPEED) {
			y_val_ = MAX_THREAT_FALL_SPEED;
		}

		if(input_type_.left_==1) {
			x_val_-= THREAT_SPEED;
		}
		else if(input_type_.right_ == 1) {
			x_val_+= THREAT_SPEED;
		}

		checkMap(gMap);
	}
	else if(think_time_>0) {
		think_time_--;
		if(think_time_ ==0) {
			InitPlayer();
		}
	}

}




void bossThreat::InitPlayer() {

	x_val_ =0;
	y_val_=0;
	if(x_pos_>256){
		x_pos_ -= 256;

	}
	else
		x_pos_= 0;
	y_pos_=0;
	think_time_ = 0;
	input_type_.left_ = 1;
}

void bossThreat::RemoveBullet(const int& idex) {

	int size =bullet_list_.size();
	if(size>0 && idex < size) {
		bulletObj* p_bullet = bullet_list_.at(idex);
		bullet_list_.erase(bullet_list_.begin() + idex);

		if(p_bullet) {
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

void bossThreat::checkMap(Map& gMap) {

	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	on_ground_ = 0;

	//kiem tra chieu ngang
	int height_min = height_frame_;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		//di chuyen sang phai
		if (x_val_ > 0) {
			int val1 = gMap.tile[y1][x2];
			int val2 = gMap.tile[y2][x2];

			if ((val1 != BLANK_SIZE && val1 != STATE_MONEY) || (val2 != BLANK_SIZE && val2 != STATE_MONEY)) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
		}
		//di chuyen sang trai
		else if (x_val_ < 0) {
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y2][x1];

			if ((val1 != BLANK_SIZE && val1 != STATE_MONEY) || (val2 != BLANK_SIZE && val2 != STATE_MONEY)) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	//kiem tra chieu doc
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {
			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];

			if ((val1 != BLANK_SIZE && val1 != STATE_MONEY) || (val2 != BLANK_SIZE && val2 != STATE_MONEY)) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_);
				y_val_ = 0;
				on_ground_ = 1;
			}
		}
		else if (y_val_ < 0) {
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y1][x2];

			if ((val1 != BLANK_SIZE && val1 != STATE_MONEY) || (val2 != BLANK_SIZE && val2 != STATE_MONEY)) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	if (x_pos_ + width_frame_ > gMap.max_x_) {
		x_pos_ = gMap.max_x_ - width_frame_ - 1;
	}
	if(y_pos_>gMap.max_y_){
		think_time_ = 60;
	}
}





void bossThreat::InitBullet(SDL_Renderer* screen) {

	bulletObj* p_bullet = new bulletObj();
	bool ret = p_bullet->LoadImg("img//bullet_boss.png", screen);
	if(ret) {

		p_bullet->set_bullet_dir(bulletObj::DIR_LEFT);
		p_bullet->set_is_move(true);
		p_bullet->SetRect(rect_.x - 50, rect_.y + height_frame_ - 30);
		p_bullet->set_x_val(15);
		bullet_list_.push_back(p_bullet);
	}
}

void bossThreat::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit) {

	if(frame_ == 18) {
		InitBullet(des);
	}
	for(int i=0;i<bullet_list_.size();i++){
		bulletObj* p_bullet = bullet_list_.at(i);
		if(p_bullet != NULL) {
			if(p_bullet->get_is_move()){
				p_bullet->HandleMove(x_limit, y_limit);
				p_bullet->Render(des);
			}
			else {
				p_bullet->Free();
				bullet_list_.erase(bullet_list_.begin() + i);
			}

		}
	}
}


#include "main.h"
#include "bossThreat.h"

bossThreat::bossThreat() {
	frame_ =0;
	x_val_=0;
	y_val_=0;
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

void bossThreat::Show() {

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

void bossThreat::DoPlayer() {
	if(comeback_time == 0) {
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
	else if(comeback_time > 0) {
		comeback_time--;
		if(comeback_time == 0) {
			InitThreats();
		}
	}

}

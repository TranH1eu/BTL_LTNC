
#include "main.h"
#include "threatsObj.h"

threatsObj::threatsObj() {

	width_frame_ =0;
	height_frame_ =0;
	x_val_=0.0;
	y_val_=0.0;
	x_pos_=0.0;
	y_pos_=0.0;
	on_ground = false;
	comeback_time =0;
	frame_ =0;

	animation_a_ =0;
	animation_b_ =0;

	input_type_.left_ = 1;
	type_move_ = STATIC_THREAT;



}

threatsObj::~threatsObj() {

}

bool threatsObj::LoadImg(std::string path, SDL_Renderer* screen) {


	bool ret = baseFunction::LoadImg(path, screen);
	if(ret){
		width_frame_ = rect_.w/THREAT_FRAME_NUM;
		height_frame_ = rect_.h;
	}
	return ret;

}

void threatsObj::set_clips() {
	if(width_frame_ >0 && height_frame_ >0) {
		frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = 2 * width_frame_;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;

        frame_clip_[3].x = 3 * width_frame_;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame_;
        frame_clip_[3].h = height_frame_;

        frame_clip_[4].x = 4 * width_frame_;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = width_frame_;
        frame_clip_[4].h = height_frame_;

        frame_clip_[5].x = 5 * width_frame_;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = width_frame_;
        frame_clip_[5].h = height_frame_;

        frame_clip_[6].x = 6 * width_frame_;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = width_frame_;
        frame_clip_[6].h = height_frame_;

        frame_clip_[7].x = 7 * width_frame_;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = width_frame_;
        frame_clip_[7].h = height_frame_;

	}
}

void threatsObj::Show(SDL_Renderer* des) {
	if(comeback_time == 0) {
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if(frame_>=8) {
			frame_ =0;
		}

		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
		SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);

	}
}

void threatsObj::DoPlayer(Map& gMap) {


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

void threatsObj::InitThreats() {

	x_val_ =0;
	y_val_ =0;
	if(x_pos_>256) {
		x_pos_ -= 256;
		animation_a_-=256;
		animation_b_ -= 256;
	}
	else {
		x_pos_ = 0;
	}
	y_pos_ = 0;
	comeback_time = 0;
	input_type_.left_ = 1;
}

void threatsObj::checkMap(Map& gMap) {

	int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //kiem tra chieu nagang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

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
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (y_val_ > 0) {
			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];

			if ((val1 != BLANK_SIZE && val1 != STATE_MONEY) || (val2 != BLANK_SIZE && val2 != STATE_MONEY)) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				on_ground = true;

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
		comeback_time = 60;
    }

}

void threatsObj::ImpMoveType(SDL_Renderer* screen) {

	if(type_move_ == STATIC_THREAT) {
		;
	}
	else {
		//th threat dan o tren mat dat
		if(on_ground == true) {
				//khi di sang ben phai qua b thi se quay lai
			if(x_pos_>  animation_b_) {
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("img//threat_level.png", screen);
			}
			else if(x_pos_< animation_a_) {
				input_type_.left_=0;
				input_type_.right_=1;
				LoadImg("img//threat_level.png", screen);
			}
		}
		else {

			if(input_type_.left_ == 1) {
				LoadImg("img//threat_level.png", screen);
			}
		}

	}
}

void threatsObj::InitBullet(bulletObj* p_bullet, SDL_Renderer* screen) {

	if(p_bullet!=NULL) {
		p_bullet->set_bullet_type(bulletObj::LASER_BULLET);
		p_bullet->LoadImgBullet(screen);
		p_bullet->set_is_move(true);
		p_bullet->set_bullet_dir(bulletObj::DIR_LEFT);
		p_bullet->SetRect(x_pos_ + 20, y_pos_ + 10);
		p_bullet->set_x_val(15);
		bullet_list_.push_back(p_bullet);

	}
}

void threatsObj::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit) {

	for(int i=0;i<bullet_list_.size();i++) {
		bulletObj* p_bullet = bullet_list_.at(i);
		if(p_bullet != NULL) {
			if(p_bullet->get_is_move()) {
				p_bullet->HandleMove(x_limit, y_limit);
				p_bullet->Render(screen);
			}
			else {
				p_bullet->set_is_move(true);
				p_bullet->SetRect(x_pos_ + 20, y_pos_ + 10);
			}
		}
	}
}




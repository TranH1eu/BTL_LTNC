#include "main.h"
#include "mainObject.h"

mainObject::mainObject() {

    frame_ = 0;
    x_pos_ = 3*TILE_SIZE; // Spawn at the third tile horizontally
    y_pos_ = 3*TILE_SIZE; // Keep the initial vertical position as it was
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    last_status_ = -1;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
    onGround = false;

    map_x_ = 0;
    map_y_ = 0;

    comeback_time_ = 0;

    money_cnt =0;

    cnt_fall = 0;

    fall_ =0;
}

mainObject::~mainObject() {

}

void mainObject::IncreaseMoney() {

	money_cnt++;
}

bool mainObject::LoadImg(std::string path, SDL_Renderer* screen) {

    bool ret = baseFunction::LoadImg(path, screen);

    if (ret == true) {
        width_frame_ = rect_.w / 8;
        height_frame_ = rect_.h;
    }
    return ret;

}

SDL_Rect mainObject::GetRectFrame() {

	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}

void mainObject::set_clips() {

    if (width_frame_ > 0 && height_frame_ > 0) {
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

void mainObject::Show(SDL_Renderer* des) {

	if(onGround == true) {

		if (status_ == WALK_LEFT) {
        	LoadImg("img//soldier_left.png", des);
    	}
    	else {
        	LoadImg("img//soldier_right.png", des);
	}

	}
	else{
		if (status_ == WALK_LEFT) {
        	LoadImg("img//jump_left.png", des);
    	}
    	else {
        	LoadImg("img//jump_right.png", des);
    	}
	}






    if (input_type_.left_ == 1 || input_type_.right_ == 1) {
        frame_++;
    }
    else frame_ = 0;
    if (frame_ >= 8) {
        frame_ = 0;
    }
    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void mainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[2]) {

    if (events.type == SDL_KEYDOWN) {
        switch (events.key.keysym.sym) {

        case SDLK_RIGHT:
            status_ = WALK_RIGHT;
            last_status_ = WALK_RIGHT;
            input_type_.right_ = 1;
            input_type_.left_ = 0;
            if(onGround == true) {
				LoadImg("img//soldier_right.png", screen);
            }
            else {
				LoadImg("img//jump_right.png", screen);
            }
            break;
        case SDLK_LEFT:
            status_ = WALK_LEFT;
            last_status_ = WALK_LEFT;
            input_type_.left_ = 1;
            input_type_.right_ = 0;
            if(onGround == true) {
				LoadImg("img//soldier_left.png", screen);
            }
            else {
				LoadImg("img//jump_left.png", screen);
            }
            break;
		 case SDLK_UP:
		 	input_type_.up_ = 1;
		 	last_status_ = WALK_UP;
            if(onGround) {
                input_type_.up_ = 1;
                if (status_ == WALK_LEFT) {
                    status_ = WALK_LEFT;  // Giữ nguyên hướng trái
                    LoadImg("img//jump_left.png", screen);
                } else if (status_ == WALK_RIGHT) {
                    status_ = WALK_RIGHT;  // Giữ nguyên hướng phải
                    LoadImg("img//jump_right.png", screen);
                }
            }

            break;

        case SDLK_DOWN:
            input_type_.down_ = 1;
            last_status_ = WALK_DOWN;
            if (status_ == WALK_LEFT) {
                status_ = WALK_LEFT;  // Giữ nguyên hướng trái
                LoadImg("img//soldier_left.png", screen);
            } else if (status_ == WALK_RIGHT) {
                status_ = WALK_RIGHT;  // Giữ nguyên hướng phải
                LoadImg("img//soldier_right.png", screen);
            }

            break;

        }
    }
    else if (events.type == SDL_KEYUP) {
        switch (events.key.keysym.sym) {
        case SDLK_RIGHT:
            input_type_.right_ = 0;
            break;
        case SDLK_LEFT:
            input_type_.left_ = 0;
            break;
		case SDLK_UP:
			input_type_.up_ = 0;
			break;
		case SDLK_DOWN:
			input_type_.down_ =0;
        }
    }
    else if (events.type == SDL_MOUSEBUTTONDOWN) {
		if(events.button.button == SDL_BUTTON_LEFT) {
			bulletObj* p_bullet = new bulletObj();
			p_bullet->LoadImg("img//gun.png", screen);
			Mix_PlayChannel(-1, bullet_sound[0], 0);

			if(last_status_ == WALK_LEFT) {
				p_bullet->set_bullet_dir(bulletObj::DIR_LEFT);
				p_bullet->SetRect(this->rect_.x, rect_.y + height_frame_ * 0.3);
			}
			else if(last_status_ == WALK_RIGHT) {
				p_bullet->set_bullet_dir(bulletObj::DIR_RIGHT);
				p_bullet->SetRect(this->rect_.x + width_frame_ -15, rect_.y + height_frame_ * 0.3);
			}
			else if(last_status_ == WALK_UP) {
				p_bullet->set_bullet_dir(bulletObj::DIR_UP);
				p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
			}
			else if(last_status_ == WALK_DOWN) {
				p_bullet->set_bullet_dir(bulletObj::DIR_DOWN);
				p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
			}


			p_bullet->set_x_val(20);
			p_bullet->set_y_val(20);
			p_bullet->set_is_move(true);

			p_bullet_list_.push_back(p_bullet);
		}
    }


}

void mainObject::HandleBullet(SDL_Renderer* des) {
	for(int i=0;i<p_bullet_list_.size();i++) {
		bulletObj* p_bullet = p_bullet_list_.at(i);
		if(p_bullet != NULL) {
			if(p_bullet->get_is_move() == true) {
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HIGHT);
				p_bullet->Render(des);
			}
			else {
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
				if(p_bullet == NULL){
					delete p_bullet;
					p_bullet = NULL;
				}

			}
		}
	}
}

void mainObject::RemoveBullet(const int& idex) {

	int size = p_bullet_list_.size();
	if(size>0 && idex < size) {
		bulletObj* p_bullet = p_bullet_list_.at(idex);
		p_bullet_list_.erase(p_bullet_list_.begin() + idex);

		if(p_bullet) {
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

void mainObject::DoPlayer(Map& map_data) {

    if(comeback_time_ ==0) {
		x_val_ = 0;

    	if (input_type_.left_ == 1) {
        	x_val_ -= PLAYER_SPEED;
    	}
    	else if (input_type_.right_ == 1) {
        	x_val_ += PLAYER_SPEED;
    	}

    	y_val_ += 0.8;
    	if (y_val_ >= MAX_FALL_SPEED) {
        	y_val_ = MAX_FALL_SPEED;
    	}

    	if (input_type_.up_ == 1) {
			if(onGround)
			{
				y_val_ = - PLAYER_JUMP_VAL;
				input_type_.up_ = 0;

			}
			onGround = false;


    	}

    	checkMap(map_data);
    	CenterEntityOnMap(map_data);
    	}
    	if(comeback_time_>0) {
			comeback_time_--;
			if(comeback_time_ ==0) {
				if(x_pos_ > 256) {
					x_pos_-=256; // 4 tile map
					map_x_ += 256;
				}
				else{
					x_pos_ =0;
				}
				y_pos_ =0;
				x_val_ = 0;
				y_val_ = 0;

			}

    	}
}

void mainObject::CenterEntityOnMap(Map& map_data) {

	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
	if(map_data.start_x_<0){
		 map_data.start_x_ =0;
	}
	else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) {
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}
	map_data.start_y_ = y_pos_ - (SCREEN_HIGHT/2);
	if(map_data.start_y_ < 0) map_data.start_y_=0;
	else if (map_data.start_y_ + SCREEN_HIGHT >= map_data.max_y_) {
		map_data.start_y_ = map_data.max_y_ - SCREEN_HIGHT;
	}

}

void mainObject::checkMap(Map& map_data) {

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

			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if(val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney();
			}
			else {
				if (val1 != BLANK_SIZE || val2 != BLANK_SIZE) {
                	x_pos_ = x2 * TILE_SIZE;
                	x_pos_ -= width_frame_ + 1;
                	x_val_ = 0;
           		}

			}


        }
        //di chuyen sang trai
        else if (x_val_ < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if(val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				IncreaseMoney();
			}
			else {
				if (val1 != BLANK_SIZE || val2 != BLANK_SIZE) {
                	x_pos_ = (x1 + 1) * TILE_SIZE;
                	x_val_ = 0;
            }

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
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if(val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney();
			}
			else {
				if (val1 != BLANK_SIZE || val2 != BLANK_SIZE) {
                	y_pos_ = y2 * TILE_SIZE;
                	y_pos_ -= (height_frame_ + 1);
                	y_val_ = 0;
                	onGround = true;

            	}
			}


        }
        else if (y_val_ < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if(val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				IncreaseMoney();
			}
			else {
				if (val1 != BLANK_SIZE || val2 != BLANK_SIZE) {
                	y_pos_ = (y1 + 1) * TILE_SIZE;
                	y_val_ = 0;
            	}
			}

        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0) {
        x_pos_ = 0;
    }
    if (x_pos_ + width_frame_ > map_data.max_x_) {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }
    if(y_pos_>map_data.max_y_){
		comeback_time_ = 60;
		cnt_fall++;
		fall_=1;


    }
    else if (y_pos_< map_data.max_y_) {
		fall_ = 0;
    }

}


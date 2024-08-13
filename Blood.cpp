
#include "main.h"
#include "Blood.h"

Blood::Blood() {

	num_ = 0;
}

Blood::~Blood() {

}

void Blood::addPos(const int& xpos) {

	pos_list_.push_back(xpos);
}

void Blood::Init(SDL_Renderer* screen) {

	LoadImg("img//blood.png", screen);
	num_ = 3;
	if(pos_list_.size() > 0) {
		pos_list_.clear();
	}

	addPos(20);
	addPos(60);
	addPos(100);
}

void Blood::Show(SDL_Renderer* screen) {

	for(int i=0;i<pos_list_.size();i++) {

		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}

void Blood::Decrease() {

	num_--;
	pos_list_.pop_back();
}

void Blood::Increase() {

	num_++;
	int last_pos = pos_list_.back();
	last_pos+=40;
	pos_list_.push_back(last_pos);
}

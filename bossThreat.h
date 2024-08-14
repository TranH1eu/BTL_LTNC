
#ifndef BOSS_THREAT_H_
#define BOSS_THREAT_H_


#include "commonFunction.h"
#include "bulletObj.h"
#include "baseFunction.h"

#define MAX_THREAT_FALL_SPEED 10
#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_SPEED 3

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

	void checkMap(Map& gMap);

	void DoPlayer(Map& gMap);
	void InitPlayer();
	std::vector<bulletObj*> get_bullet_list() const {return bullet_list_;}
	void set_bullet_list(const std::vector<bulletObj*>& am_list) {bullet_list_ = am_list;}

	SDL_Rect GetRectFrame();

	void RemoveBullet(const int& idex);

	void InitBullet(SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);

	void DecreaseHealth() { health_ -= 10; } // Giảm máu mỗi lần bị bắn trúng
    int GetHealth() const { return health_; }
    void SetHealth(int health) { health_ = health; }

    void IncreaseHitCount() { hit_cnt_++; }  // Tăng biến đếm
	int GetHitCount() const { return hit_cnt_; } // Lấy giá trị biến đếm
private:
	int map_x_;
	int map_y_;
	int on_ground_;
	int think_time_;
	int frame_;
	SDL_Rect frame_clip_[FRAME_NUM_32];
	int x_pos_;
	int y_pos_;
	float x_val_;
	float y_val_;
	int width_frame_;
	int height_frame_;
	Input input_type_;
	 int health_ = 100;

	 int hit_cnt_;
	std::vector<bulletObj*> bullet_list_;

};

#endif // BOSS_THREAT_H_

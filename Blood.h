
#ifndef BLOOD_H_
#define BLOOD_H_

#include "commonFunction.h"
#include "baseFunction.h"

class Blood : public baseFunction {

public:
	Blood();
	~Blood();

	void setNum(const int& num) {num_ = num;}
	void addPos(const int& xpos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);

	void Increase();
	void Decrease();

private:
	int num_;
	std::vector<int> pos_list_;


};

#endif // BLOOD_H_

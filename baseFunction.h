
#ifndef BASE_FUNCTION_H_
#define BASE_FUNCTION_H_

#include "commonFunction.h"

class baseFunction {

public:
	baseFunction();
	~baseFunction();

	void SetRect(const int& x, const int& y) {rect_.x =x, rect_.y =y;}
	SDL_Rect GetRect() const {return rect_;}
	SDL_Texture* GetObject() const {return p_object_;}


	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};

#endif // BASE_FUNCTION_H

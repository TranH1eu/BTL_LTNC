
#ifndef MENU_H_
#define MENU_H_

#include "commonFunction.h"
#include "baseFunction.h"
#include "textDisplay.h"



class menuObj : public baseFunction {
public:
    menuObj();
    ~menuObj();

    bool LoadMenu(SDL_Renderer* screen);
    void HandleMenuEvents(SDL_Event& e, bool& start_game, bool& quit_game);
    void RenderMenu(SDL_Renderer* screen);

private:
    textObjstartText;
    textDisplay exitText;
    SDL_Texture* background_;
};

#endif // MENU_H_

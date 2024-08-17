
#include "menuObj.h"
#include "main.h"
#include<iostream>

menuObj::menuObj() {
    background_ = NULL;
}

menuObj::~menuObj() {
    if (background_ != NULL) {
        SDL_DestroyTexture(background_);
        background_ = NULL;
    }
}

bool menuObj::LoadMenu(SDL_Renderer* screen) {
    baseFunction background;
    if (!background.LoadImg("img//blue.png", screen)) {
        std::cerr << "Error: Failed to load background image." << std::endl;
        return -1;
    }
    background_ = background.GetObject();

    // Check if the background texture was loaded successfully
    if (background_ == NULL) {
        std::cerr << "Error: Background texture is NULL after loading." << std::endl;
        return false;
    }

    // Load text for menu options
    TTF_Font* font = TTF_OpenFont("font//font.ttf", 15);
    if (font == NULL) {
        std::cerr << "Error: Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    startText.setText("Start Game");
    startText.setColor(textDisplay::WHITE_TEXT);
    if (!startText.LoadFromRenderText(font, screen)) {
        std::cerr << "Error: Failed to render start game text." << std::endl;
        TTF_CloseFont(font);
        return false;
    }

    exitText.setText("Exit");
    exitText.setColor(textDisplay::WHITE_TEXT);
    if (!exitText.LoadFromRenderText(font, screen)) {
        std::cerr << "Error: Failed to render exit text." << std::endl;
        TTF_CloseFont(font);
        return false;
    }

    TTF_CloseFont(font);
    return true;
}



void menuObj::HandleMenuEvents(SDL_Event& e, bool& start_game, bool& quit_game) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_1:
            start_game = true;  // Bắt đầu trò chơi
            break;
        case SDLK_2:
            quit_game = true;   // Thoát trò chơi
            break;
        }
    }
}

void menuObj::RenderMenu(SDL_Renderer* screen) {
    if (background_ != NULL) {
        SDL_RenderCopy(screen, background_, NULL, NULL);
    } else {
        std::cerr << "Error: Background texture is NULL." << std::endl;
    }

    // Render text options
    startText.RenderText(screen, SCREEN_WIDTH / 2 - 100, SCREEN_HIGHT / 2 - 50);
    exitText.RenderText(screen, SCREEN_WIDTH / 2 - 100, SCREEN_HIGHT / 2);
}




#include "main.h"
#include "commonFunction.h"
#include "baseFunction.h"

#include <iostream>

bool SDLCommonFunc::LoadImg(std::string path, SDL_Renderer* screen) {

    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface == NULL) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

    p_object_ = SDL_CreateTextureFromSurface(screen, load_surface);
    if (p_object_ == NULL) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(load_surface);
        return false;
    }

    rect_.w = load_surface->w;
    rect_.h = load_surface->h;

    SDL_FreeSurface(load_surface);
    return true;
}

void SDLCommonFunc::Render(SDL_Renderer* des, const SDL_Rect* clip) {


    // Đảm bảo p_object_ đã được gán giá trị hợp lệ trước khi sử dụng
    if (p_object_ != NULL) {
        SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
        SDL_RenderCopy(des, p_object_, clip, &renderquad);
    } else {
        std::cerr << "No texture to render!" << std::endl;
    }


}


void SDLCommonFunc::Free() {


	if(p_object_ ==NULL) {
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}

bool SDLCommonFunc::checkFocusWithRect(const int& x, const int& y, const SDL_Rect& rect) {
    std::cout << "Checking: (" << x << ", " << y << ") against Rect: ("
              << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")" << std::endl;

    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}


int SDLCommonFunc::showMenu(SDL_Renderer* des, TTF_Font* font) {
    bool ret = LoadImg("img//background.png", des);
    if (!ret) {
        std::cerr << "Failed to load background image" << std::endl;
        return 1;
    }
    const int kMenuItem = 2;
    SDL_Rect pos_arr[kMenuItem];


    // Định nghĩa khu vực cho nút "Play Game"
    SDL_Rect playGameArea = {550, 400, 150, 50}; // x, y, width, height

    // Định nghĩa khu vực cố định để thoát game
    SDL_Rect exitArea = {570, 500, 100, 50}; // x, y, width, height

    textDisplay txt_menu[kMenuItem];
    txt_menu[0].setText("Play Game");
    txt_menu[0].setColor(textDisplay::WHITE_TEXT);
    txt_menu[1].setText("Exit");
    txt_menu[1].setColor(textDisplay::WHITE_TEXT);

    for (int i = 0; i < kMenuItem; i++) {
        if (!txt_menu[i].LoadFromRenderText(font, des)) {
            std::cerr << "Failed to load text for menu item " << i << std::endl;
            return 1;
        }
    }

    // Tính toán vị trí chính xác cho chữ "Exit" để nó nằm giữa vùng đen
    SDL_Rect exitTextRect = txt_menu[1].GetRect();
    pos_arr[1].x = exitArea.x + (exitArea.w - exitTextRect.w) / 2 - 30;
    pos_arr[1].y = exitArea.y + (exitArea.h - exitTextRect.h) / 2 - 10;

    SDL_Rect playTextRect = txt_menu[1].GetRect();
    pos_arr[0].x = playGameArea.x + (playGameArea.w - playTextRect.w) / 2 - 65;
    pos_arr[0].y = playGameArea.y + (playGameArea.h - playTextRect.h) / 2 - 10;

    bool selected[kMenuItem] = { false, false };
    SDL_Event m_event;

    while (true) {
        SDL_RenderClear(des);
        SDLCommonFunc::Render(des, nullptr);
        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type) {
                case SDL_QUIT:
                    Free();
                    return 0;
                case SDL_MOUSEMOTION: {
                    int xm = m_event.motion.x;
                    int ym = m_event.motion.y;
                    selected[0] = (xm >= playGameArea.x && xm <= playGameArea.x + playGameArea.w &&
                                   ym >= playGameArea.y && ym <= playGameArea.y + playGameArea.h);
                    selected[1] = (xm >= exitArea.x && xm <= exitArea.x + exitArea.w &&
                                   ym >= exitArea.y && ym <= exitArea.y + exitArea.h);
                }
                break;
                case SDL_MOUSEBUTTONDOWN: {
                    int xm = m_event.button.x;
                    int ym = m_event.button.y;
                    if (xm >= playGameArea.x && xm <= playGameArea.x + playGameArea.w &&
                        ym >= playGameArea.y && ym <= playGameArea.y + playGameArea.h) {
                        // Xử lý khi nhấn "Play Game"

                        return 2; // Trả về 2 để chỉ ra rằng một trò chơi mới đã được khởi động
                    }
                    if (xm >= exitArea.x && xm <= exitArea.x + exitArea.w &&
                        ym >= exitArea.y && ym <= exitArea.y + exitArea.h) {
                        Free();
                        return 1;
                    }
                }
                break;
                case SDL_KEYDOWN:
                    if (m_event.key.keysym.sym == SDLK_ESCAPE) {
                        Free();
                        return 0;
                    }
                break;
            }
        }

        // Cập nhật màu sắc của text dựa trên trạng thái selected
        txt_menu[0].setColor(selected[0] ? textDisplay::RED_TEXT : textDisplay::WHITE_TEXT);
        txt_menu[0].LoadFromRenderText(font, des);
        txt_menu[1].setColor(selected[1] ? textDisplay::RED_TEXT : textDisplay::WHITE_TEXT);
        txt_menu[1].LoadFromRenderText(font, des);

        // Vẽ hình chữ nhật đen cho "Play Game"
        SDL_SetRenderDrawColor(des, 0, 0, 0, 255); // Màu đen
        SDL_RenderFillRect(des, &playGameArea);

        // Vẽ hình chữ nhật đen cho "Exit"
        SDL_SetRenderDrawColor(des, 0, 0, 0, 255); // Màu đen
        SDL_RenderFillRect(des, &exitArea);

        // Render text
        for (int i = 0; i < kMenuItem; i++) {
            txt_menu[i].RenderText(des, pos_arr[i].x, pos_arr[i].y);
        }
        SDL_RenderPresent(des);
    }
    Free();
    return 1;
}


bool SDLCommonFunc::collisionCheck(const SDL_Rect& object1, const SDL_Rect& object2) {

    // Lấy các cạnh của object1
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    // Lấy các cạnh của object2
    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // Kiểm tra nếu object1 nằm ngoài object2
    if (right_a <= left_b || left_a >= right_b || bottom_a <= top_b || top_a >= bottom_b) {
        return false;  // Không có va chạm
    }

    // Nếu không nằm ngoài, thì có va chạm
    return true;
}




	#include "main.h"
	#include "commonFunction.h"

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

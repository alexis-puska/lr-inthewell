#include "HitBox.h"

HitBox::HitBox() {
}

void HitBox::initHitBox(int x, int y, int hitBoxWidth, int hitBoxHeight) {
    this->hitBoxWidth = hitBoxWidth;
    this->hitBoxHeight = hitBoxHeight;
    updateHitBox(x, y);
}

HitBox::~HitBox() {
    
}

SDL_Rect HitBox::getRect() {
    return rect;
}

void HitBox::updateHitBox(int x, int y) {
    rect.x = x;
    rect.y = y;
    rect.w = hitBoxWidth;
    rect.h = hitBoxHeight;
}

bool HitBox::hit(SDL_Rect other) {
   // std::cout << "hit rect : "<< rect.x << " " << rect.y << " " << rect.w << " " << rect.h << " other : " << other.x << " " << other.y << " " << other.w << " " << other.h << " \n";
    return SDL_HasIntersection(&rect, &other);
}

bool HitBox::hitMeByBottonOrTopSide(SDL_Rect other) {
    SDL_Rect result;
    int x1 = rect.x;
    int y1 = rect.y;
    int x2 = rect.x + rect.w;
    int y2 = rect.y;
    if(SDL_IntersectRectAndLine(&other, &x1, &y1, &x2, &y2)){
        if(SDL_IntersectRect(&other, &rect, &result)){
            if(result.w >= result.h){
                std::cout << "on me touche en haut !\n";
                return true;
            }
        }
    }
    x1 = rect.x;
    y1 = rect.y + rect.h;
    x2 = rect.x + rect.w;
    y2 = rect.y + rect.h;
    if(SDL_IntersectRectAndLine(&other, &x1, &y1, &x2, &y2)){
        if(SDL_IntersectRect(&other, &rect, &result)){
            if(result.w >= result.h){
                std::cout << "on me touche en bas !\n";
                return true;
            }
        }
    }
    return false;
}



int HitBox::getIntersect(SDL_Rect other, bool horizontal) {
    SDL_Rect result;
    SDL_IntersectRect(&rect, &other, &result);
    if (horizontal) {
        return result.h;
    } else {
        return result.w;
    }
}


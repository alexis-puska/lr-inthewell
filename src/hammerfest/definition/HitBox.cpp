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
    return SDL_HasIntersection(&rect, &other);
}

bool HitBox::hitMeByLeftSide(SDL_Rect other) {
    SDL_Rect result;
    if(SDL_IntersectRect(&other, &rect, &result)){
        if(result.h > result.w){
            return true;
        }
    }
    return false;
}

bool HitBox::hitMeByRightSide(SDL_Rect other) {
    SDL_Rect result;
    if(SDL_IntersectRect(&other, &rect, &result)){
        if(result.h > result.w){
            return true;
        }
    }
    return false;
}

bool HitBox::hitMeByBottonSide(SDL_Rect other) {
    int x1 = other.x;
    int y1 = other.y;
    int x2 = other.x + other.w;
    int y2 = other.y;
    if(SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2)){
        SDL_Rect result;
        if(SDL_IntersectRect(&other, &rect, &result)){
            if(result.w >= result.h){
                return true;
            }
        }
    }
    return false;
}

bool HitBox::hitMeByTopSide(SDL_Rect other) {
    int x1 = other.x;
    int y1 = other.y + other.h;
    int x2 = other.x + other.w;
    int y2 = other.y + other.h;
    if(SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2)){
        SDL_Rect result;
        if(SDL_IntersectRect(&other, &rect, &result)){
            if(result.w >= result.h){
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

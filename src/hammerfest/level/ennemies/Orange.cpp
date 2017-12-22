#include "Orange.h"

Orange::Orange(int id, int x, int y, Level * level) :
Ennemie(id, x, y, orange, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Orange::~Orange() {
}

void Orange::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

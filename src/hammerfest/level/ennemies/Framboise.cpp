#include "Framboise.h"

Framboise::Framboise(int id, int x, int y, Level * level) :
Ennemie(id, x, y, framboise, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Framboise::~Framboise() {
}

void Framboise::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

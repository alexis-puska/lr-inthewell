#include "NainBricot.h"

NainBricot::NainBricot(int id, int x, int y, Level *level) :
Ennemie(id, x, y, nainbricot, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

NainBricot::~NainBricot() {
}

void NainBricot::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

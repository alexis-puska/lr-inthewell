#include "Kiwi.h"

Kiwi::Kiwi(int id, int x, int y) :
Ennemie(id, x, y, kiwi) {
    this->state = frozed;
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Kiwi::~Kiwi() {
}

void Kiwi::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

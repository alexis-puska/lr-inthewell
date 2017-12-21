#include "Ananas.h"

Ananas::Ananas(int id, int x, int y) :
Ennemie(id, x, y, ananas) {
    this->state = frozed;
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Ananas::~Ananas() {
}

void Ananas::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

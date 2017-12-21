#include "Poire.h"

Poire::Poire(int id, int x, int y) :
Ennemie(id, x, y, poire) {
    this->state = frozed;
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Poire::~Poire() {
}

void Poire::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

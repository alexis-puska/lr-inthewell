#include "Scie.h"

Scie::Scie(int id, int x, int y, Level *level) :
Ennemie(id, x, y, scie, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Scie::~Scie() {
}

void Scie::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

#include "Ananas.h"

Ananas::Ananas(int id, int x, int y, Level * level) :
Ennemie(id, x, y, ananas, level) {
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

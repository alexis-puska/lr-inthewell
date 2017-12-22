#include "Banane.h"

Banane::Banane(int id, int x, int y, Level *level) :
Ennemie(id, x, y, banane, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Banane::~Banane() {
}

void Banane::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

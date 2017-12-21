#include "Blob.h"

Blob::Blob(int id, int x, int y) :
Ennemie(id, x, y, blob) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Blob::~Blob() {
}

void Blob::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

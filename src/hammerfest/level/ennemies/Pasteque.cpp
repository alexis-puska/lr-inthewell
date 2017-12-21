#include "Pasteque.h"

Pasteque::Pasteque(int id, int x, int y) :
Ennemie(id, x, y, pasteque) {
    this->state = frozed;
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Pasteque::~Pasteque() {
}

void Pasteque::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

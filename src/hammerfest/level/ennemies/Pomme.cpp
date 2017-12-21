#include "Pomme.h"

Pomme::Pomme(int id, int x, int y) :
Ennemie(id, x, y, pomme) {
    this->state = frozed;
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Pomme::~Pomme() {
}

void Pomme::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

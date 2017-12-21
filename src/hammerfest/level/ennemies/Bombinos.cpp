#include "Bombinos.h"

Bombinos::Bombinos(int id, int x, int y) :
	Ennemie(id, x, y, bombinos) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Bombinos::~Bombinos() {
}

void Bombinos::doSomething(SDL_Surface * dest) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

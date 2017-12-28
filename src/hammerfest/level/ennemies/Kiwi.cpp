#include "Kiwi.h"

Kiwi::Kiwi(int id, int x, int y, Level *level) :
Ennemie(id, x, y, kiwi, level) {
}

Kiwi::~Kiwi() {
}

void Kiwi::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    switch (whatITouch()) {
        case nothing:
            move();
            break;
        case wall:
        case edge:
        case bottomStairs:
		case bottomHighStairs:
        case topStaires:
        case edgeCanJump:
            changeDirection();
            move();
            break;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Kiwi::iMove(){
}
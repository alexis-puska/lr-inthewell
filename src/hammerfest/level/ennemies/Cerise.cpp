#include "Cerise.h"

Cerise::Cerise(int id, int x, int y, Level * level) :
Ennemie(id, x, y, cerise, level) {
}

Cerise::~Cerise() {
}

void Cerise::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    iMove();
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Cerise::iMove(){
    switch (whatITouch()) {
        case nothing:
            move();
            break;
        case wall:
        case edge:
        case bottomStairs:
        case topStaires:
        case edgeCanJump:
            changeDirection();
            move();
            break;
    }
}
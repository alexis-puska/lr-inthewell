#include "Citron.h"

Citron::Citron(int id, int x, int y, Level * level) :
    Ennemie(id, x, y, citron, level) {
}

Citron::~Citron() {
}

void Citron::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    switch(state){
        case walk:
        case angry:
            iMove();
            break;
        case jump:
            ennemieJump();
            break;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Citron::iMove(){
    switch (whatITouch()) {
        case nothing:
            move();
            break;
        case edgeCanJump:
        case edge:
            if (plateformFrontMe()) {
                changeState(jump);
                initJump(direction, 0);
            }
            else {
                changeDirection();
                move();
            }
            break;
        case wall:
        case bottomHighStairs:
        case bottomStairs:
        case topStaires:
            changeDirection();
            move();
            break;
    }

}
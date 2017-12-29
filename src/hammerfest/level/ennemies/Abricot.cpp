#include "Abricot.h"

Abricot::Abricot(int id, int x, int y, Level *level) :
Ennemie(id, x, y, abricot, level) {
}

Abricot::~Abricot() {
}

void Abricot::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    bool endAnimationReach = false;
    if (animIdx >= animIdxMax) {
        endAnimationReach = true;
    }
    
    int distPlateformAbove = plateformAbove();
    
    SDL_Surface * sprite = NULL;
    
    switch (state) {
        case look:
            if (endAnimationReach) {
                changeState(jump);
            }
            break;
        case jump:
            ennemieJump();
            break;
        case walk:
            if (choice(160) && distPlateformAbove > 0) {
                changeState(look);
                initJump(up, distPlateformAbove);
                break;
            }
            iMove();
            break;
    }
    
    if (endAnimationReach) {
        animIdx = 0;
    }
    
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Abricot::iMove() {
    switch (whatITouch()) {
        case nothing:
            move();
            break;
        case bottomStairs:
            changeState(jump);
            initJump(up, 1);
            break;
        case topStaires:
            changeState(jump);
            initJump(down, 0);
            break;
        case wall:
            changeDirection();
            move();
            break;
        case edgeCanJump:
            if (choice(10)) {
                changeState(jump);
                initJump(down, 0);
                break;
            }
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
        case bottomHighStairs:
            if (choice(10)) {
                changeState(jump);
                initJump(up, getStepSize());
                break;
            }
    }
}
#include "Banane.h"

Banane::Banane(int id, int x, int y, Level *level) :
Ennemie(id, x, y, banane, level) {
}

Banane::~Banane() {
}

void Banane::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    bool endAnimationReach = false;
    if(animIdx >= animIdxMax){
        endAnimationReach = true;
    }
    
    SDL_Surface * sprite = NULL;
    
    switch(state){
        case look:
            
        case jump:
            ennemieJump();
            break;
        case walk:
            iMove();
            break;
    }
    
    if (endAnimationReach) {
        animIdx = 0;
    }
    
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Banane::iMove(){
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
        case edge:
            changeDirection();
            move();
            break;
        case edgeCanJump:
            changeState(jump);
            initJump(down, 0);
            break;
    }
}
#include "Pomme.h"

Pomme::Pomme(int id, int x, int y, Level * level) :
Ennemie(id, x, y, pomme, level) {
}

Pomme::~Pomme() {
}

void Pomme::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    
    switch(state){
        case jump:
            ennemieJump();
            break;
        case walk:
            iMove();
            break;
    }
    
	
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Pomme::iMove(){
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
        case edgeCanJump:
            changeDirection();
            move();
            break;
    }
}
#include "Orange.h"

Orange::Orange(int id, int x, int y, Level * level) :
	Ennemie(id, x, y, orange, level) {
	animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Orange::~Orange() {
}

void Orange::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
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
            break;
    }
    
    
	sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
	drawHimself(sprite, dest);
}

void Orange::iMove(){
    switch (whatITouch()) {
        case nothing:
            move();
            break;
        case wall:
        case edgeCanJump:
            std::cout<<(plateformFrontMe()?"canjump platform found\n":"");
            changeDirection();
            move();
            break;
        case edge:
            std::cout<<(plateformFrontMe()?"platform found\n":"");
        case bottomStairs:
        case topStaires:
            changeDirection();
            move();
            break;
    }
}
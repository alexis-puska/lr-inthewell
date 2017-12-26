#include "Pomme.h"

Pomme::Pomme(int id, int x, int y, Level * level) :
Ennemie(id, x, y, pomme, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Pomme::~Pomme() {
}

void Pomme::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
	switch (whatITouch()) {
	case nothing:
		move();
		break;
	case bottomStairs:
		setY(getY() - 20);
		move(); 
		break;
	case topStaires:
		setY(getY() + 20);
		move(); 
		break;
	case wall:
	case edge:
	case edgeCanJump:
		changeDirection();
		move();
		break;
	}
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Pomme::iMove(){
}
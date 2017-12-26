#include "Banane.h"

Banane::Banane(int id, int x, int y, Level *level) :
Ennemie(id, x, y, banane, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Banane::~Banane() {
}

void Banane::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
	switch (whatITouch()) {
	case nothing:
		move();
		break;
	case bottomStairs:
		setY(getY()-20);
		move(); move(); move();
		break;
	case topStaires:
		setY(getY()+20);
		move(); move(); move();
		break;
	case wall:
		changeDirection();
		move();
		break;
	case edge:
		changeDirection();
		move();
		break;
	case edgeCanJump:
		changeDirection();
		move();
		break;
	}
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Banane::iMove(){
}
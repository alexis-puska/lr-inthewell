#include "Cerise.h"

Cerise::Cerise(int id, int x, int y, Level * level) :
	Ennemie(id, x, y, cerise, level) {
	animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Cerise::~Cerise() {
}

void Cerise::doSomething(SDL_Surface * dest) {
	SDL_Surface * sprite = NULL;
	if (animIdx >= animIdxMax) {
		animIdx = 0;
	}
	sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
	drawHimself(sprite, dest);
}

#include "Pasteque.h"



Pasteque::Pasteque(int id, int x, int y) :
	Ennemie(id, x, y, pasteque) {
	this->type = pasteque;
	this->id = id;
	this->animIdx = 0;
	initHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight, ennemieHitboxWidth, ennemieHitboxHeight);
	animIdxMax = Sprite::Instance().getAnimationSize("pasteque_walk");
}


Pasteque::~Pasteque() {
}

void Pasteque::doSomething(SDL_Surface * dest) {
	SDL_Surface * t = NULL;
	if (animIdx >= animIdxMax) {
		animIdx = 0;
	}
	t = Sprite::Instance().getAnimation("pasteque_walk", animIdx);
	copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + leftPadding, y - (t->h));
	updateHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight);
	SDL_Rect * rect = new SDL_Rect;
	rect->h = this->getRect().h;
	rect->w = this->getRect().w;
	rect->x = this->getRect().x + leftPadding;
	rect->y = this->getRect().y;
	SDL_FillRect(dest, rect, SDL_MapRGB(dest->format, 255, 0, 0));
	animIdx++;
}

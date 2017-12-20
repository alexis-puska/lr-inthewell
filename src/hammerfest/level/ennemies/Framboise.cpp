#include "Framboise.h"



Framboise::Framboise(int id, int x, int y) :
	Ennemie(id, x, y, framboise) {
	this->type = framboise;
	this->id = id;
	this->animIdx = 0;
	initHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight, ennemieHitboxWidth, ennemieHitboxHeight);
	animIdxMax = Sprite::Instance().getAnimationSize("framboise_walk");
}


Framboise::~Framboise() {
}

void Framboise::doSomething(SDL_Surface * dest) {
	SDL_Surface * t = NULL;
	if (animIdx >= animIdxMax) {
		animIdx = 0;
	}
	t = Sprite::Instance().getAnimation("framboise_walk", animIdx);
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

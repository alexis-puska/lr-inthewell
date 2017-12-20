#include "Blob.h"



Blob::Blob(int id, int x, int y) :
	Ennemie(id, x, y, blob) {
	this->type = blob;
	this->id = id;
	this->animIdx = 0;
	initHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight, ennemieHitboxWidth, ennemieHitboxHeight);
	animIdxMax = Sprite::Instance().getAnimationSize("blob_walk");
}


Blob::~Blob() {
}

void Blob::doSomething(SDL_Surface * dest) {
	SDL_Surface * t = NULL;
	if (animIdx >= animIdxMax) {
		animIdx = 0;
	}
	t = Sprite::Instance().getAnimation("blob_walk", animIdx);
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
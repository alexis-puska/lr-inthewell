#include "Ennemie.h"

Ennemie::Ennemie(int id, int x, int y, int type) :
Position((x * 20) +10 , (y * 20) + 20), Drawable(), HitBox(), IdElement(id) {
	this->type = type;
	this->animIdx = 0;
	this->state = walk;
	initHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight, ennemieHitboxWidth, ennemieHitboxHeight);
}

Ennemie::~Ennemie() {
    
}

void Ennemie::doSomething(SDL_Surface * dest) {
}

void Ennemie::drawHimself(SDL_Surface * sprite, SDL_Surface * dest) {
	copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w / 2)) + leftPadding, y - (sprite->h));
	updateHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight);
	SDL_Rect * rect = new SDL_Rect;
	rect->h = this->getRect().h;
	rect->w = this->getRect().w;
	rect->x = this->getRect().x + leftPadding; 
	rect->y = this->getRect().y;
	SDL_FillRect(dest, rect, SDL_MapRGB(dest->format, 255, 0, 0));
	animIdx++;
}

std::string Ennemie::getStateString() {
	std::stringstream ss;
	ss << ennemieTypeString[this->type] << "_" << ennemieStateString[this->state];
	return ss.str();
}


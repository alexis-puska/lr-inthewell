#include "Rayon.h"

Rayon::Rayon(int x, int y, int length, int type, bool vertical) :
		Drawable(), Position(x, y), HitBox() {
	this->length = length;
	this->type = type;
	this->vertical = vertical;
	//initHitBox(x, y, width - vortexHitboxBorder, height - vortexHitboxBorder);
}

Rayon::~Rayon() {

}

int Rayon::getType() {
	return this->type;
}

void Rayon::drawHimself(SDL_Surface * dest){

}

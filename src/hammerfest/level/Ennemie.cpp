#include "Ennemie.h"

Ennemie::Ennemie(int id, int x, int y, int type) :
		Position(x, y), Drawable(), HitBox(), IdElement(id) {
	this->type = type;
}

Ennemie::~Ennemie() {

}

void Ennemie::drawHimself(SDL_Surface * dest) {

}

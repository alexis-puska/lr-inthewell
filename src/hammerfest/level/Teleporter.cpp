#include "Teleporter.h"

Teleporter::Teleporter(int id, int x, int y, int length, bool vertical, int toId) :
		Drawable(), Position(x, y), IdElement(id) {
	this->length = length;
	this->vertical = vertical;
	this->toId = toId;
	//initHitBox(x, y, width - vortexHitboxBorder, height - vortexHitboxBorder);
}

Teleporter::~Teleporter() {

}

void Teleporter::drawHimself(SDL_Surface * dest){

}

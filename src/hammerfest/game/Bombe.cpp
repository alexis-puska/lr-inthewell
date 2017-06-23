#include "Bombe.h"

Bombe::Bombe(int x, int y, int type) :
		Position(x, y),Drawable() {
	this->type = type;
}

Bombe::~Bombe() {
}

#include "Vortex.h"

Vortex::Vortex(int id, int x, int y, double zoomX, double zoomY, bool enable, int destination) :
		Drawable(), Position(x, y), HitBox(), IdElement(id) {
	this->zoomX = zoomX;
	this->zoomY = zoomY;
	this->enable = enable;
	this->destination = destination;
	this->animationPosition = 0;
	this->animation = Sprite::Instance().getAnimation("vortex");
	this->width = floor(animation[0]->w * zoomX);
	this->height = floor(animation[0]->h * zoomY);
	initHitBox(x, y, width - vortexHitboxBorder, height - vortexHitboxBorder);
}

Vortex::~Vortex() {

}

void Vortex::enableVortex() {
	this->enable = true;
}

bool Vortex::isEnable() {
	return this->enable;
}

int Vortex::getDestination() {
	return this->destination;
}

void Vortex::drawHimself(SDL_Surface * dest) {
	if (this->enable) {
		copySurfaceToBackRenderer(rotozoomSurfaceXY(animation[animationPosition], 0, zoomX, zoomY, 0), dest, (x - (width / 2))+leftPadding, y - height);
		this->animationPosition++;
		if ((unsigned) this->animationPosition > animation.size() - 1) {
			this->animationPosition = 0;
		}
	}
}

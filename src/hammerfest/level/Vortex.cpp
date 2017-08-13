#include "Vortex.h"

Vortex::Vortex(int id, int x, int y, double zoomX, double zoomY, bool enable, int destination, int animationType) :
		Drawable(), Position(x, y), HitBox(), IdElement(id) {
	this->zoomX = zoomX;
	this->zoomY = zoomY;
	this->enable = enable;
	this->destination = destination;
	this->animationPosition = 0;
	this->animation = Sprite::Instance().getAnimation("vortex");
	this->width = (int)floor(animation[0]->w * zoomX);
	this->height = (int)floor(animation[0]->h * zoomY);
	this->animationType = animationType;
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
		SDL_Surface * temp = rotozoomSurfaceXY(animation[animationPosition], 0, zoomX, zoomY, 0);
		copySurfaceToBackRenderer(temp, dest, (x - (width / 2))+leftPadding, y - height);
		SDL_FreeSurface(temp);
		this->animationPosition++;
		if ((unsigned) this->animationPosition > animation.size() - 1) {
			this->animationPosition = 0;
		}
	}
}

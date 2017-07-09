#include "Decor.h"

Decor::Decor(int id, int x, int y, bool displayed, bool background, std::string animation, int indexAnimation) :
		Drawable(), Position(x, y), IdElement(id) {
	this->displayed = displayed;
	this->background = background;
	this->animation = animation;
	this->indexAnimation = indexAnimation;
}

Decor::~Decor() {
}

void Decor::display() {
	this->displayed = true;
}

bool Decor::isOnBackground() {
	return background;
}

void Decor::drawHimself(SDL_Surface * dest) {
	fprintf(stderr, "dcor : %i %i %s %i\n",x, y, animation.c_str(),indexAnimation);
	if (this->displayed) {
		SDL_Surface * tmp = Sprite::Instance().getAnimation(animation,indexAnimation);
		copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
	}
}

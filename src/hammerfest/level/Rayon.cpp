#include "Rayon.h"

Rayon::Rayon(int x, int y, int length, int type, bool vertical) :
		Drawable(), Position(x, y), HitBox() {
	this->length = length;
	this->type = type;
	this->vertical = vertical;
	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0xff000000;
	buffer = new SDL_Surface*[2];
	if (vertical) {
		for (int i = 0; i < 2; i++) {
			buffer[i] = SDL_CreateRGBSurface(0, 20, 20 * length, 32, rmask, gmask, bmask, amask);
			for (int j = 0; j < length; j++) {
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("rayon", i == 0 ? type * 2 : type * 2 + 1), buffer[i], 0, gridSize * j, gridSize, gridSize);
			}
		}
	} else {
		for (int i = 0; i < 2; i++) {
			buffer[i] = SDL_CreateRGBSurface(0, 20 * length, 20, 32, rmask, gmask, bmask, amask);
			for (int j = 0; j < length; j++) {
				copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("rayon", i == 0 ? type * 2 : type * 2 + 1), 90, 1, 0), buffer[i], 20 * j, 0, gridSize, gridSize);
			}
		}
	}
}

Rayon::~Rayon() {
	for (int i = 0; i < 2; i++) {
		SDL_FreeSurface(buffer[i]);
	}
	delete buffer;
}

int Rayon::getType() {
	return this->type;
}

void Rayon::drawHimself(SDL_Surface * dest) {
	//fprintf(stderr,"draw rayon\n");
	if (animation) {
		copySurfaceToBackRenderer(buffer[0], dest, x * gridSize, y * gridSize);
		animation = false;
	} else {
		copySurfaceToBackRenderer(buffer[1], dest, x * gridSize, y * gridSize);
		animation = true;
	}
	//fprintf(stderr,"fin draw rayon\n");
}

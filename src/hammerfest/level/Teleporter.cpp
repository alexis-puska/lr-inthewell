#include "Teleporter.h"

Teleporter::Teleporter(int id, int x, int y, int length, bool vertical, int toId) :
		Drawable(), Position(x, y), IdElement(id) {
	this->length = length;
	this->vertical = vertical;
	this->toId = toId;
	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0xff000000;
	if (vertical) {
		buffer = SDL_CreateRGBSurface(0, 20, bufferSize * teleporterSpriteSize, 32, rmask, gmask, bmask, amask);
		for (int j = 0; j < bufferSize; j++) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("teleporter", 0), buffer, 0, teleporterSpriteSize * j);
		}
	} else {
		buffer = SDL_CreateRGBSurface(0, bufferSize * teleporterSpriteSize, 20, 32, rmask, gmask, bmask, amask);
		for (int j = 0; j < bufferSize; j++) {
			copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("teleporter", 0), 90, 1, 0), buffer, teleporterSpriteSize * j, 0);
		}
	}
	offsetAnimation = 0;
}

Teleporter::~Teleporter() {
	SDL_FreeSurface(buffer);
}

void Teleporter::drawHimself(SDL_Surface * dest) {
	fprintf(stderr,"start draw teleporter\n");
	offsetAnimation++;
	if ((offsetAnimation + (length * gridSize)) > teleporterSpriteSize * bufferSize) {
		offsetAnimation = 0;
	}

	if (vertical) {
		fprintf(stderr,"start draw teleporter vertical\nbase\n");
		copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("base_teleporter", 0), 90, 1, 0), dest, x * gridSize + 4, y * gridSize);
		fprintf(stderr,"start draw teleporter vertical\nbase\n");
		copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("base_teleporter", 0), 270, 1, 0), dest, x * gridSize + 4, y * gridSize + gridSize * length - 8);
		fprintf(stderr,"start draw teleporter vertical\nflux\n");
		copySurfaceToBackRenderer(buffer, dest, x * gridSize, (y * gridSize) + 11, 20, (length * gridSize) - 22);

	} else {
		fprintf(stderr,"start draw teleporter horizontal\nbase\n");
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("base_teleporter", 0), dest, x * gridSize, y * gridSize + 4);
		fprintf(stderr,"start draw teleporter horizontal\nbase\n");
		copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("base_teleporter", 0), 180, 1, 0), dest, x * gridSize + gridSize * length - 8, y * gridSize + 4);
		fprintf(stderr,"start draw teleporter horizontal\nflux\n");
		copySurfaceToBackRenderer(buffer, dest, (x * gridSize) + 8, y * gridSize, (length * gridSize) - 16, 20);
	}
}
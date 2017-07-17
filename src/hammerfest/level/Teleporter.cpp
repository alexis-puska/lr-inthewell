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
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("teleporter", 1), buffer, 0, teleporterSpriteSize * j);
		}
	} else {
		buffer = SDL_CreateRGBSurface(0, bufferSize * teleporterSpriteSize, 20, 32, rmask, gmask, bmask, amask);
		for (int j = 0; j < bufferSize; j++) {
			copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("teleporter", 1), 90, 1, 0), buffer, teleporterSpriteSize * j, 0);
		}
	}
	offsetAnimation = 0;
}

Teleporter::~Teleporter() {
	SDL_FreeSurface(buffer);
}

void Teleporter::drawHimself(SDL_Surface * dest) {
	//fprintf(stderr,"start draw teleporter\n");
	offsetAnimation+=16;
	if ((offsetAnimation + (length * gridSize)) > teleporterSpriteSize * bufferSize) {
		offsetAnimation = 0;
	}

	// 8 X 11
	if (vertical) {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("base_teleporter", 2), dest, (x * gridSize)+leftPadding, y * gridSize);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("base_teleporter", 3), dest, (x * gridSize)+leftPadding, (y + length-1) * gridSize);
		//fprintf(stderr,"start draw teleporter vertical\nflux\n");
		copySurfaceToBackRendererWithStartOffset(buffer, dest, (x * gridSize)+leftPadding, (y * gridSize) + 6, 20, ((length * gridSize) - 10), 0, offsetAnimation);

	} else {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("base_teleporter", 0), dest, (x * gridSize)+leftPadding, y * gridSize);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("base_teleporter", 1), dest, ((x + length-1) * gridSize)+leftPadding, y * gridSize);
		copySurfaceToBackRendererWithStartOffset(buffer, dest, ((x * gridSize) + 6)+leftPadding, y * gridSize, (length * gridSize) -10, 20, offsetAnimation , 0);
	}
}
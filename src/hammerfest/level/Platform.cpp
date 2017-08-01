#include "Platform.h"

Platform::Platform(int id, int x, int y, bool vertical, bool visible, int length, int surfaceId) :
		Drawable(), Position(x, y), IdElement(id), HitBox() {
	this->vertical = vertical;
	this->visible = visible;
	this->length = length;
	this->surfaceId = surfaceId;
	if (vertical) {
		initHitBox(x * 20, y * 20, 20, length * 20);
	} else {
		initHitBox(x * 20, y * 20, length * 20, 20);
	}

}

Platform::~Platform() {
}

bool Platform::isVertical() {
	return this->vertical;
}

int Platform::getLength() {
	return this->length;
}

void Platform::drawHimself(SDL_Surface * dest) {
	if (visible) {
		if (vertical) {
			Uint32 rmask, gmask, bmask, amask;
			amask = 0xff000000;
			rmask = 0x00ff0000;
			gmask = 0x0000ff00;
			bmask = 0x000000ff;
			SDL_Surface * temp = SDL_CreateRGBSurface(0, length * gridSize, gridSize, 32, rmask, gmask, bmask, amask);
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("platform", surfaceId), temp, 0, 0, ((length * gridSize) - 6), -1);
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("end_platform", surfaceId), temp, ((length * gridSize) - 6), 0, -1, -1);
			SDL_Surface * temp2 = rotozoomSurfaceXY(temp, 270, 1, -1, 0);
			copySurfaceToBackRenderer(temp2, dest, ((x * gridSize) - (temp2->w % 10)) + leftPadding, (y * gridSize) - ((temp2->h % 10) / 2));
			SDL_FreeSurface(temp);
			SDL_FreeSurface(temp2);
		} else {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("platform", surfaceId), dest, (x * gridSize) + leftPadding,
					(y * gridSize), ((length * gridSize) - 6), -1);
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("end_platform", surfaceId), dest,
					(((x * gridSize) + (length * gridSize)) - 6) + leftPadding, (y * gridSize), -1, -1);
		}
	}
}


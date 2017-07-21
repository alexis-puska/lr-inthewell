#include "Platform.h"

Platform::Platform(int id, int x, int y, bool vertical, bool visible, int lenght, int surfaceId) :
		Drawable(), Position(x,y), IdElement(id) {
	this->vertical = vertical;
	this->visible = visible;
	this->lenght = lenght;
	this->surfaceId = surfaceId;
}

Platform::~Platform() {
}

void Platform::drawHimself(SDL_Surface * dest) {
	if (visible) {
		if (vertical) {
			Uint32 rmask, gmask, bmask, amask;
			amask = 0xff000000;
			rmask = 0x00ff0000;
			gmask = 0x0000ff00;
			bmask = 0x000000ff;
			SDL_Surface * temp = SDL_CreateRGBSurface(0, lenght * gridSize, gridSize, 32, rmask, gmask, bmask, amask);
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("platform", surfaceId), temp, 0, 0, ((lenght * gridSize) - 6), -1);
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("end_platform", surfaceId), temp, ((lenght * gridSize) - 6), 0, -1, -1);
			SDL_Surface * temp2 = rotozoomSurfaceXY(temp,270,1,-1,0);
			copySurfaceToBackRenderer(temp2, dest, ((x * gridSize)- (temp2->w%10))+leftPadding, (y * gridSize) - ((temp2->h%10)/2));
			SDL_FreeSurface(temp);
			SDL_FreeSurface(temp2);
		} else {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("platform", surfaceId), dest, (x * gridSize)+leftPadding, (y * gridSize), ((lenght * gridSize) - 6), -1);
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("end_platform", surfaceId), dest, (((x * gridSize) + (lenght * gridSize)) - 6)+leftPadding, (y * gridSize), -1, -1);
		}
	}
}

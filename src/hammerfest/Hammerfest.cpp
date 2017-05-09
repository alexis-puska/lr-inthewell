#include "Hammerfest.h"

#include <time.h>

int main(int argc, char** argv) {

}

Hammerfest::Hammerfest(SDL_Surface * vout_bufLibretro) {

	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0xff000000;

	//init all surface
	screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
	screenBuffer = SDL_LoadBMP("background.bmp");
	vout_buf = vout_bufLibretro;
	SDL_FillRect(vout_buf, NULL, SDL_MapRGB(vout_buf->format, 255, 204, 0));
	copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);

}

Hammerfest::~Hammerfest() {

}

void Hammerfest::copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y) {
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = src->w;
	dstRect.h = src->h;
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = src->w;
	srcRect.h = src->h;
	SDL_BlitSurface(src, &srcRect, dest, &dstRect);
}

void Hammerfest::tick(unsigned short in_keystateLibretro[16]) {
	SDL_FillRect(vout_buf, NULL, SDL_MapRGB(vout_buf->format, 255, 204, 0));
	copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
}
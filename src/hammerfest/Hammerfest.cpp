#include "Hammerfest.h"

int main(int argc, char** argv) {

}

enum keyPad {
	keyPadSelect = 1,
	keyPadL3 = 2,
	keyPadR3 = 4,
	keyPadStart = 8,
	keyPadUp = 16,
	keyPadRight = 32,
	keyPadDown = 64,
	keyPadLeft = 128,
	keyPadL2 = 256,
	keyPadR2 = 512,
	keyPadL1 = 1024,
	keyPadR1 = 2048,
	keyPadX = 4096,
	keyPadA = 8192,
	keyPadB = 16384,
	keyPadY = 32768
};

Hammerfest::Hammerfest(SDL_Surface * vout_bufLibretro, char * saveFilePath, bool newSaveFile) {

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
	Sound::Instance();
	Sound::Instance().startMusicBoss();
	ItemFileSystem::Instance().init(saveFilePath, newSaveFile);
	//TODO a degager
	ItemFileSystem::Instance().loadAccount(0);
}

Hammerfest::~Hammerfest() {
	SDL_FreeSurface(screenBuffer);
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

void Hammerfest::keyPressed() {
	int index = 0;
	anyPlayerkeychange = false;
	for (int i = 0; i < 2; i++) {
		if (previousPlayerKeystate[i] != in_keystate[index]) {
			keychange[i] = true;
			anyPlayerkeychange = true;
			previousPlayerKeystate[i] = in_keystate[index];
		} else {
			keychange[i] = false;
		}
		index++;
	}
}

void Hammerfest::tick(unsigned short in_keystateLibretro[2]) {
	SDL_FillRect(vout_buf, NULL, SDL_MapRGB(vout_buf->format, 255, 204, 0));
	copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
	for (int i = 0; i < 2; i++) {
		in_keystate[i] = in_keystateLibretro[i];
	}
	keyPressed();
	if (previousPlayerKeystate[0] & keyPadStart && keychange[0]) {
		fprintf(stderr, "play sound\n");
		Sound::Instance().playSoundBlackBombe();
	}

	//ItemFileSystem::Instance().loadAccount(0);
	ItemFileSystem::Instance().simulateGame();
	//ItemFileSystem::Instance().save(4400000, true, 110);
}

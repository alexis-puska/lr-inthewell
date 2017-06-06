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

enum menuStep {
	splashMenu = 0, saveMenu, modeMenu, optionMenu
};

Hammerfest::Hammerfest(SDL_Surface * vout_bufLibretro, char * saveFilePath, bool newSaveFile) {
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0xff000000;

	//init all surface
	screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
	vout_buf = vout_bufLibretro;
	SDL_FillRect(vout_buf, NULL, SDL_MapRGB(vout_buf->format, 255, 204, 0));
	drawMenu = 0;
	selectedSavedGame = 0;
	redrawMenu = true;
	Sprite::Instance();
	Sound::Instance();
	Sound::Instance().startMusicBoss();
	ItemFileSystem::Instance().init(saveFilePath, newSaveFile);
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

void Hammerfest::fillScreenBufferWithSurface(std::string name, int index) {
	SDL_Surface * temp2 = Sprite::Instance().getAnimation(name, 0);
	int x = 0;
	int y = 0;
	while (y < 520) {
		while (x < 420) {
			copySurfaceToBackRenderer(temp2, screenBuffer, x, y);
			x += temp2->w;
		}
		x = 0;
		y += temp2->h;
	}
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

	/**********************
	 * MENU MOVE
	 *********************/
	switch (drawMenu) {
		case splashMenu:
			if (previousPlayerKeystate[0] & keyPadA && keychange[0]) {
				drawMenu = saveMenu;
				redrawMenu = true;
			}
			break;
		case saveMenu:
			if (previousPlayerKeystate[0] & keyPadB && keychange[0]) {
				drawMenu = splashMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadA && keychange[0]) {
				drawMenu = modeMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadUp && keychange[0]) {
				selectedSavedGame--;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadDown && keychange[0]) {
				selectedSavedGame++;
				redrawMenu = true;
			}
			break;
		case modeMenu:
			if (previousPlayerKeystate[0] & keyPadB && keychange[0]) {
				drawMenu = saveMenu;
				redrawMenu = true;
			}
			break;
		case optionMenu:
			break;
	}

	/**********************
	 * DRAW PART
	 *********************/
	switch (drawMenu) {
		case splashMenu:
			drawSplashScreen();
			break;
		case saveMenu:
			drawSaveGameMenu();
			break;
		case modeMenu:
			drawGameModeMenu();
			break;
		case optionMenu:
			drawGameOptionMenu();
			break;
	}
}

/******************************
 *      DRAW SPLASH SCREN
 ******************************/
void Hammerfest::drawSplashScreen() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_1", 0);
		SDL_Surface * temp = Sprite::Instance().getAnimation("menu_title", 0);
		copySurfaceToBackRenderer(temp, screenBuffer, (420 - temp->w) / 2, (520 - temp->h) / 2);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

/******************************
 * DRAW LOADING SAVE GAME MENU
 *****************************/
void Hammerfest::drawSaveGameMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_1", 0);
		for (int i = 0; i < 4; i++) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_player", i), screenBuffer, 67, 147 + (90 * i));
			if (i != selectedSavedGame) {
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_ice", 0), screenBuffer, 60, 140 + (90 * i));
			}
		}
		Sprite::Instance().drawText(screenBuffer, 210, 30, "Chargez votre", red, true);
		Sprite::Instance().drawText(screenBuffer, 210, 60, "sauvegarde", red, true);
		Sprite::Instance().drawText(screenBuffer, 150, 167, "IGOR", red, false);
		Sprite::Instance().drawText(screenBuffer, 150, 257, "SANDY", red, false);
		Sprite::Instance().drawText(screenBuffer, 150, 347, "TUBERCULOZ", red, false);
		Sprite::Instance().drawText(screenBuffer, 150, 437, "WANDA", red, false);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

/**************************
 *    DRAW GAME MODE MENU
 *************************/
void Hammerfest::drawGameModeMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_1", 0);
		SDL_Surface * temp = Sprite::Instance().getAnimation("menu_title", 0);
		copySurfaceToBackRenderer(temp, screenBuffer, (420 - temp->w) / 2, (520 - temp->h) / 2);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

void Hammerfest::drawGameOptionMenu() {

}

void Hammerfest::drawFridgeMenu() {

}

void Hammerfest::drawQuestMenu() {

}

//ItemFileSystem::Instance().loadAccount(0);
//ItemFileSystem::Instance().simulateGame();
//ItemFileSystem::Instance().save(4400000, true, 110);

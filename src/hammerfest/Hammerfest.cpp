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
	splashMenu = 0, saveMenu, modeMenu, optionMenu, mainMenu, fridgeMenu, questMenu
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
	drawNextMenu = modeMenu;
	redrawMenu = true;
	fridgeItemPosition = 0;
	fridgeFirstItemView = 0;
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

	/**********************
	 * MENU MOVE
	 *********************/
	switch (drawMenu) {
		case splashMenu:
			if (previousPlayerKeystate[0] & keyPadStart && keychange[0]) {
				drawMenu = saveMenu;
				redrawMenu = true;
			}
			break;
		case saveMenu:
			if (previousPlayerKeystate[0] & keyPadSelect && keychange[0]) {
				drawMenu = splashMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadStart && keychange[0]) {
				ItemFileSystem::Instance().loadAccount(GameConfig::Instance().getGameLoaded());
				drawMenu = mainMenu;
				drawNextMenu = modeMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadUp && keychange[0]) {
				GameConfig::Instance().decGameLoaded();
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadDown && keychange[0]) {
				GameConfig::Instance().incGameLoaded();
				redrawMenu = true;
			}
			break;
		case mainMenu:
			if (previousPlayerKeystate[0] & keyPadSelect && keychange[0]) {
				drawMenu = saveMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadStart && keychange[0]) {
				drawMenu = drawNextMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadUp && keychange[0]) {
				if (drawNextMenu == modeMenu) {
					drawNextMenu = questMenu;
				} else if (drawNextMenu == fridgeMenu) {
					drawNextMenu = modeMenu;
				} else if (drawNextMenu == questMenu) {
					drawNextMenu = fridgeMenu;
				}
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadDown && keychange[0]) {
				if (drawNextMenu == modeMenu) {
					drawNextMenu = fridgeMenu;
				} else if (drawNextMenu == fridgeMenu) {
					drawNextMenu = questMenu;
				} else if (drawNextMenu == questMenu) {
					drawNextMenu = modeMenu;
				}
				redrawMenu = true;
			}
			break;

		case modeMenu:
			if (previousPlayerKeystate[0] & keyPadSelect && keychange[0]) {
				drawMenu = mainMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadStart && keychange[0]) {
				drawMenu = optionMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadUp && keychange[0]) {
				GameConfig::Instance().decGameMode();
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadDown && keychange[0]) {
				GameConfig::Instance().incGameMode();
				redrawMenu = true;
			}
			break;
		case optionMenu:
			if (previousPlayerKeystate[0] & keyPadSelect && keychange[0]) {
				drawMenu = modeMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadStart && keychange[0]) {
				drawMenu = modeMenu;
				redrawMenu = true;
			}
			break;

		case fridgeMenu:
			if (previousPlayerKeystate[0] & keyPadSelect && keychange[0]) {
				drawMenu = mainMenu;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadUp && keychange[0]) {
				fridgeItemPosition -= 6;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadDown && keychange[0]) {
				GameConfig::Instance().incGameMode();
				fridgeItemPosition += 6;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadLeft && keychange[0]) {
				GameConfig::Instance().decGameMode();
				fridgeItemPosition -= 1;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadRight && keychange[0]) {
				GameConfig::Instance().incGameMode();
				fridgeItemPosition += 1;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadL1 && keychange[0]) {
				fridgeItemPosition -= 42;
				fridgeFirstItemView -= 42;
				redrawMenu = true;
			} else if (previousPlayerKeystate[0] & keyPadR1 && keychange[0]) {
				GameConfig::Instance().incGameMode();
				fridgeItemPosition += 42;
				fridgeFirstItemView += 42;
				redrawMenu = true;
			}
			break;
		case questMenu:
			if (previousPlayerKeystate[0] & keyPadSelect && keychange[0]) {
				drawMenu = mainMenu;
				redrawMenu = true;
			}
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
		case mainMenu:
			drawMainMenu();
			break;
		case fridgeMenu:
			drawFridgeMenu();
			break;
		case questMenu:
			drawQuestMenu();
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
		fillScreenBufferWithSurface("menu_background_2", 0);
		for (int i = 0; i < 4; i++) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_player", i), screenBuffer, 67, 147 + (90 * i));
			if (i != GameConfig::Instance().getGameLoaded()) {
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
 *    DRAW MAIN MENU
 *************************/
void Hammerfest::drawMainMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		Sprite::Instance().drawText(screenBuffer, 210, 30, "MAIN", red, true);
		for (int i = 0; i < 3; i++) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game", i), screenBuffer, 127, 147 + (90 * i));
		}
		Sprite::Instance().drawText(screenBuffer, 210, 167, "JOUER", red, false);
		Sprite::Instance().drawText(screenBuffer, 210, 257, "FRIGO", red, false);
		Sprite::Instance().drawText(screenBuffer, 210, 347, "QUETES", red, false);
		if (drawNextMenu == modeMenu) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 110, 167);
		} else if (drawNextMenu == fridgeMenu) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 110, 257);
		} else if (drawNextMenu == questMenu) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 110, 347);
		}
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

/*
 *menu_background_1"},
 menu_background_2"},
 menu_title"},
 menu_image_1"},
 menu_player"},
 menu_ice"},
 menu_cursor"},
 menu_game"},
 menu_game_option"},
 menu_game_checkbox"}
 */

/**************************
 *    DRAW GAME MODE MENU
 *************************/
void Hammerfest::drawGameModeMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		Sprite::Instance().drawText(screenBuffer, 210, 30, "GAME MODE", red, true);
		for (int i = 0; i < 5; i++) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_option", i), screenBuffer, 107, 147 + (60 * i));
		}
		Sprite::Instance().drawText(screenBuffer, 170, 147, "SOLO", red, false);
		Sprite::Instance().drawText(screenBuffer, 170, 207, "APPRENTISAGE", red, false);
		Sprite::Instance().drawText(screenBuffer, 170, 267, "TIMEATTACK", red, false);
		Sprite::Instance().drawText(screenBuffer, 170, 327, "MULTI", red, false);
		Sprite::Instance().drawText(screenBuffer, 170, 387, "SOCCER", red, false);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 75, 147 + GameConfig::Instance().getGameMode() * 60);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

/**************************
 *    DRAW GAME OPTION MENU
 *************************/
void Hammerfest::drawGameOptionMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		SDL_Surface * temp = Sprite::Instance().getAnimation("menu_title", 0);
		copySurfaceToBackRenderer(temp, screenBuffer, (420 - temp->w) / 2, (520 - temp->h) / 2);
		Sprite::Instance().drawText(screenBuffer, 210, 30, "GAME OPTION", red, true);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

/**************************
 *    DRAW FRIDGE MENU
 *************************/
void Hammerfest::drawFridgeMenu() {
	if (redrawMenu) {
		char tmp[50];
		fillScreenBufferWithSurface("menu_background_2", 0);
		Sprite::Instance().drawText(screenBuffer, 210, 0, "CONTENU DU FRIGO", red, true);
		//navigate thiw object, 42 object dislpayed (6 columns x 7 lines)
		if (fridgeItemPosition < 0) {
			fridgeItemPosition = 0;
		} else if (fridgeItemPosition > 352) {
			fridgeItemPosition = 352;
			fridgeFirstItemView = 312;
		}
		if (fridgeItemPosition < fridgeFirstItemView) {
			fridgeFirstItemView -= 6;
		} else if (fridgeItemPosition > fridgeFirstItemView + 41) {
			fridgeFirstItemView += 6;
		}
		if (fridgeFirstItemView < 0) {
			fridgeFirstItemView = 0;
		} else if (fridgeFirstItemView > 312) {
			fridgeFirstItemView = 312;
		}
		fprintf(stderr, "cursor : %i %i\n", fridgeItemPosition, fridgeFirstItemView);
		int index = fridgeFirstItemView;
		int qty = 0;
		for (int y = 0; y < 7; y++) {
			for (int x = 0; x < 6; x++) {
				if (index > 352) {
					break;
				}
				qty = ItemFileSystem::Instance().getQuantity(index);
				if (qty > 0) {
					copySurfaceToBackRenderer(Sprite::Instance().getAnimation("objects", index), screenBuffer, 10 + (x * 63), 10 + (61 * y));
				} else {
					copySurfaceToBackRenderer(Sprite::Instance().getAnimation("objects", 353), screenBuffer, 10 + (x * 63), 10 + (61 * y));
				}
				sprintf(tmp, "%i", qty);
				Sprite::Instance().drawTextVerdana(screenBuffer, 40 + (x * 63), 72 + (61 * y), tmp, white, true);
				index++;
			}
		}
		if (ItemFileSystem::Instance().getQuantity(fridgeItemPosition) > 0) {
			sprintf(tmp, "%s", ItemFileSystem::Instance().getItem(fridgeItemPosition)->getName());
		} else {
			sprintf(tmp, "???????");
		}
		Sprite::Instance().drawTextVerdana(screenBuffer, 210, 500, tmp, white, true);
		int pos = fridgeItemPosition - fridgeFirstItemView;
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 10 + (pos % 6) * 63, 50 + (floor(pos / 6)) * 61);
		fprintf(stderr, "cursor : %i %i\n", fridgeItemPosition, fridgeFirstItemView);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

/**************************
 *    DRAW QUEST MENU
 *************************/
void Hammerfest::drawQuestMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		SDL_Surface * temp = Sprite::Instance().getAnimation("menu_title", 0);
		copySurfaceToBackRenderer(temp, screenBuffer, (420 - temp->w) / 2, (520 - temp->h) / 2);
		Sprite::Instance().drawText(screenBuffer, 210, 30, "QUEST", red, true);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

//ItemFileSystem::Instance().loadAccount(0);
//ItemFileSystem::Instance().simulateGame();
//ItemFileSystem::Instance().save(4400000, true, 110);

#include "Hammerfest.h"

int main(int argc, char** argv) {

}

enum menuStep {
	splashMenu = 0, saveMenu, modeMenu, optionMenu, mainMenu, fridgeMenu, questMenu, gameStep
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
	game = NULL;
	fridgeItemPosition = 0;
	fridgeFirstItemView = 0;
	questSelect = 0;
	firstQuestView = 0;
	cursorPosition = 0;
	Sprite::Instance();
	LevelService::Instance();
	Sound::Instance().startMusicBoss();
	ItemFileSystem::Instance().init(saveFilePath, newSaveFile);
}

Hammerfest::~Hammerfest() {
	if (game) {
		if (game->isConfigured()) {
			if (game->isAlive()) {
				game->exitGame();
			}
		}
		delete game;
	}
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
	for (int i = 0; i < 2; i++) {
		in_keystate[i] = in_keystateLibretro[i];
	}
	keyPressed();
	/**********************
	 * MENU MOVE
	 *********************/
	/**********************
	 * PRESS SELECT
	 *********************/
	if (drawMenu != gameStep) {
		if (previousPlayerKeystate[0] & keyPadSelect && keychange[0]) {
			switch (drawMenu) {
				case saveMenu:
					drawMenu = splashMenu;
					break;
				case modeMenu:
					drawMenu = mainMenu;
					break;
				case optionMenu:
					drawMenu = modeMenu;
					break;
				case mainMenu:
					drawMenu = saveMenu;
					break;
				case fridgeMenu:
					drawMenu = mainMenu;
					break;
				case questMenu:
					drawMenu = mainMenu;
					break;
			}
			redrawMenu = true;
		}
		/**********************
		 * PRESS START
		 *********************/
		if (previousPlayerKeystate[0] & keyPadStart && keychange[0]) {
			switch (drawMenu) {
				case splashMenu:
					drawMenu = saveMenu;
					break;
				case saveMenu:
					ItemFileSystem::Instance().loadAccount(GameConfig::Instance().getGameLoaded());
					drawMenu = mainMenu;
					drawNextMenu = modeMenu;
					break;
				case modeMenu:
					drawMenu = optionMenu;
					break;
				case optionMenu:
					/*******************
					 *    START GAME
					 *******************/
					drawMenu = gameStep;
					game = new Game(vout_buf, in_keystate);
					break;
				case mainMenu:
					drawMenu = drawNextMenu;
					break;
			}
			redrawMenu = true;
		}
		/**********************
		 * PRESS UP
		 *********************/
		if (previousPlayerKeystate[0] & keyPadUp && keychange[0]) {
			switch (drawMenu) {
				case saveMenu:
					GameConfig::Instance().decGameLoaded();
				case mainMenu:
					if (drawNextMenu == modeMenu) {
						drawNextMenu = questMenu;
					} else if (drawNextMenu == fridgeMenu) {
						drawNextMenu = modeMenu;
					} else if (drawNextMenu == questMenu) {
						drawNextMenu = fridgeMenu;
					}
					break;
				case modeMenu:
					GameConfig::Instance().decGameMode();
					cursorPosition = 0;
					break;
				case optionMenu:
					switch (GameConfig::Instance().getGameMode()) {
						case soloMode:
							cursorPosition--;
							if (cursorPosition < 0) {
								cursorPosition = 4;
							}
							break;
						case multicoopMode:
							cursorPosition--;
							if (cursorPosition < 0) {
								cursorPosition = 2;
							}
							break;
						case soccerMode:
							cursorPosition--;
							if (cursorPosition < 0) {
								cursorPosition = 5;
							}
							break;
					}
					break;
				case fridgeMenu:
					fridgeItemPosition -= 6;
					break;
				case questMenu:
					questSelect -= 1;
					break;
			}
			redrawMenu = true;
		}
		/**********************
		 * PRESS DOWN
		 *********************/
		if (previousPlayerKeystate[0] & keyPadDown && keychange[0]) {
			switch (drawMenu) {
				case saveMenu:
					GameConfig::Instance().incGameLoaded();
					redrawMenu = true;
					break;
				case mainMenu:
					if (drawNextMenu == modeMenu) {
						drawNextMenu = fridgeMenu;
					} else if (drawNextMenu == fridgeMenu) {
						drawNextMenu = questMenu;
					} else if (drawNextMenu == questMenu) {
						drawNextMenu = modeMenu;
					}
					break;
				case modeMenu:
					GameConfig::Instance().incGameMode();
					cursorPosition = 0;
					break;
				case optionMenu:
					switch (GameConfig::Instance().getGameMode()) {
						case soloMode:
							cursorPosition++;
							if (cursorPosition > 4) {
								cursorPosition = 0;
							}
							break;
						case learningMode:
							break;
						case timeAttackMode:
							break;
						case multicoopMode:
							cursorPosition++;
							if (cursorPosition > 2) {
								cursorPosition = 0;
							}
							break;
						case soccerMode:
							cursorPosition++;
							if (cursorPosition > 5) {
								cursorPosition = 0;
							}
							break;
					}
					break;
				case fridgeMenu:
					fridgeItemPosition += 6;
					break;
				case questMenu:
					questSelect += 1;
					break;
			}
			redrawMenu = true;
		}
		/**********************
		 * PRESS LEFT
		 *********************/
		if (previousPlayerKeystate[0] & keyPadLeft && keychange[0]) {
			if (drawMenu == fridgeMenu) {
				fridgeItemPosition -= 1;
				redrawMenu = true;
			}
		}
		/**********************
		 * PRESS RIGHT
		 *********************/
		if (previousPlayerKeystate[0] & keyPadRight && keychange[0]) {
			if (drawMenu == fridgeMenu) {
				fridgeItemPosition += 1;
				redrawMenu = true;
			}
		}
		/**********************
		 * PRESS L1
		 *********************/
		if (previousPlayerKeystate[0] & keyPadL1 && keychange[0]) {
			switch (drawMenu) {
				case fridgeMenu:
					fridgeItemPosition -= 42;
					fridgeFirstItemView -= 42;
					break;
				case questMenu:
					questSelect -= 10;
					firstQuestView -= 10;
					break;
			}
			redrawMenu = true;
		}
		/**********************
		 * PRESS R1
		 **********************/
		if (previousPlayerKeystate[0] & keyPadR1 && keychange[0]) {
			switch (drawMenu) {
				case fridgeMenu:
					fridgeItemPosition += 42;
					fridgeFirstItemView += 42;
					break;
				case questMenu:
					questSelect += 10;
					firstQuestView += 10;
					break;
			}
			redrawMenu = true;
		}
		/**********************
		 * PRESS A
		 *********************/
		if (previousPlayerKeystate[0] & keyPadA && keychange[0]) {
			if (drawMenu == optionMenu) {
				switch (GameConfig::Instance().getGameMode()) {
					case soloMode:
						GameConfig::Instance().toogleSoloOption(cursorPosition);

						break;
					case multicoopMode:
						GameConfig::Instance().toogleMultiOption(cursorPosition);
						break;
					case soccerMode:
						if (cursorPosition < 2) {
							GameConfig::Instance().toogleSoccerOption(cursorPosition);
						} else {
							GameConfig::Instance().setSoccerMap(cursorPosition - 2);
						}
						break;
				}
				redrawMenu = true;
			}
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
				switch (GameConfig::Instance().getGameMode()) {
					case soloMode:
						drawGameOptionSoloMenu();
						break;
					case learningMode:
						drawGameOptionLearningMenu();
						break;
					case timeAttackMode:
						drawGameOptionTimeAttackMenu();
						break;
					case multicoopMode:
						drawGameOptionMultiMenu();
						break;
					case soccerMode:
						drawGameOptionSoccerMenu();
						break;
				}
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
	} else {
		if (game->isRequestStopGame()) {
			previousPlayerKeystate[0] = in_keystate[0];
			game->exitGame();
			delete game;
			game = NULL;
			drawMenu = optionMenu;
		}
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
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 30, "Chargez votre", red, true);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 60, "sauvegarde", red, true);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 150, 167, "IGOR", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 150, 257, "SANDY", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 150, 347, "TUBERCULOZ", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 150, 437, "WANDA", red, false);
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
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 30, "MAIN", red, true);
		for (int i = 0; i < 3; i++) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game", i), screenBuffer, 127, 147 + (90 * i));
		}
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 167, "JOUER", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 257, "FRIGO", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 347, "QUETES", red, false);
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

/**************************
 *    DRAW GAME MODE MENU
 *************************/
void Hammerfest::drawGameModeMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 30, "GAME MODE", red, true);
		for (int i = 0; i < 5; i++) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_option", i), screenBuffer, 107, 147 + (60 * i));
		}
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 147, "SOLO", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 207, "APPRENTISAGE", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 267, GameConfig::Instance().isTimeAttackUnlock() ? "TIMEATTACK" : "???", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 327, GameConfig::Instance().isMulticoopUnlock() ? "MULTI" : "???", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 387, "SOCCER", red, false);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 75, 147 + GameConfig::Instance().getGameMode() * 60);
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
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 0, "Contenu du frigo", red, true);
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
		int index = fridgeFirstItemView;
		int qty = 0;
		//draw item with quantity
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
				Text::Instance().drawText(screenBuffer, "verdana10pt10", 40 + (x * 63), 72 + (61 * y), tmp, white, true);
				index++;
			}
		}
		//draw item name
		if (ItemFileSystem::Instance().getQuantity(fridgeItemPosition) > 0) {
			Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 500, ItemFileSystem::Instance().getItem(fridgeItemPosition)->getName().c_str(), white, true);
		} else {
			Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 500, "???????", white, true);
		}

		//draw item position
		sprintf(tmp, "%i / 353", fridgeItemPosition + 1);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 480, tmp, white, true);
		//draw cursor
		int pos = fridgeItemPosition - fridgeFirstItemView;
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 10 + (pos % 6) * 63, 50 + (floor(pos / 6)) * 61);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

/**************************
 *    DRAW QUEST MENU
 *************************/
void Hammerfest::drawQuestMenu() {
	if (redrawMenu) {
		if (questSelect < 0) {
			questSelect = 0;
			firstQuestView = 0;
		} else if (questSelect > 75) {
			questSelect = 75;
			firstQuestView = 66;
		}
		if (questSelect < firstQuestView) {
			firstQuestView = questSelect;
		} else if (questSelect > firstQuestView + 9) {
			firstQuestView = questSelect - 9;
		}
		if (firstQuestView < 0) {
			questSelect = 0;
			firstQuestView = 0;
		}
		fillScreenBufferWithSurface("menu_background_2", 0);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 0, "Les quetes", red, true);

		//draw list of quest
		int index = firstQuestView;
		std::map<int, Quest *> questsStarted = ItemFileSystem::Instance().getQuestStarted();
		std::map<int, Quest *> questsCompleted = ItemFileSystem::Instance().getQuestCompleted();
		std::stringstream ss;
		for (int i = 0; i < 10; i++) {
			ss.str(std::string());
			if (questsStarted[index] != NULL) {
				ss << index << " / 75 - " << questsStarted[index]->getTitre();
				Text::Instance().drawText(screenBuffer, "verdana10pt10", 40, i * 12 + 30, ss.str().c_str(), gold, false);
			} else if (questsCompleted[index] != NULL) {
				ss << index << " / 75 - " << questsCompleted[index]->getTitre();
				Text::Instance().drawText(screenBuffer, "verdana10pt10", 40, i * 12 + 30, ss.str().c_str(), green, false);
			} else {
				ss << index << " / 75 - ??????????";
				Text::Instance().drawText(screenBuffer, "verdana10pt10", 40, i * 12 + 30, ss.str().c_str(), red, false);
			}
			index++;
		}
		//draw cursor
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 10, (12 * (questSelect - firstQuestView)) + 24);

		//draw content of quest
		//item

		Quest * quest = ItemFileSystem::Instance().getQuest(questSelect);
		if (questsStarted[questSelect] != NULL || questsCompleted[questSelect] != NULL) {
			std::map<int, int> requiredItem = quest->getRequireItemId();
			int x = 0;
			int y = 0;
			int offsetX = 21;
			int offsetX2 = 52;

			switch (requiredItem.size()) {
				case 1:
					offsetX = 178;
					offsetX2 = 21;
					break;
				case 2:
					offsetX = 147;
					offsetX2 = 21;
					break;
				case 3:
					offsetX = 115;
					offsetX2 = 21;
					break;
				case 4:
					offsetX = 84;
					offsetX2 = 21;
					break;
				case 5:
					offsetX = 52;
					offsetX2 = 21;
					break;
				case 6:
					offsetX = 21;
					offsetX2 = 21;
					break;
				case 7:
					offsetX = 21;
					offsetX2 = 178;
					break;
				case 8:
					offsetX = 21;
					offsetX2 = 147;
					break;
				case 9:
					offsetX = 21;
					offsetX2 = 115;
					break;
				case 10:
					offsetX = 21;
					offsetX2 = 84;
					break;
				case 11:
					offsetX = 21;
					offsetX2 = 52;
					break;
				case 12:
					offsetX = 21;
					offsetX2 = 21;
					break;
			}

			for (std::map<int, int>::iterator it = requiredItem.begin(); it != requiredItem.end(); ++it) {
				if (y == 0) {
					copySurfaceToBackRenderer(Sprite::Instance().getAnimation("objects", it->first), screenBuffer, offsetX + (x * 63), 200 + (61 * y));
					ss.str(std::string());
					ss << ItemFileSystem::Instance().getQuantity(it->first) << "/" << it->second;
					Text::Instance().drawText(screenBuffer, "verdana10pt10", offsetX + 31 + (x * 63), 263 + (61 * y), ss.str().c_str(), white, true);
				} else {
					copySurfaceToBackRenderer(Sprite::Instance().getAnimation("objects", it->first), screenBuffer, offsetX2 + (x * 63), 200 + (61 * y));
					ss.str(std::string());
					ss << ItemFileSystem::Instance().getQuantity(it->first) << "/" << it->second;
					Text::Instance().drawText(screenBuffer, "verdana10pt10", offsetX2 + 31 + (x * 63), 263 + (61 * y), ss.str().c_str(), white, true);
				}
				x++;
				if (x >= 6) {
					x = 0;
					y++;
				}
			}
		} else {
			Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 200, "???", white, true);
		}

		//description
		if (questsStarted[questSelect] != NULL) {
			Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 352, "???", white, true);
		} else if (questsCompleted[questSelect] != NULL) {
			int idx = 0;
			int offsetY = 0;
			int lastSpace = 0;
			while (true) {
				if ((unsigned)idx >= quest->getDescription().size() - 1) {
					Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 352 + offsetY * 12, quest->getDescription().substr(lastSpace, idx - lastSpace).c_str(), white, true);
					break;
				} else if (quest->getDescription().at(idx) == ' ') {
					if (idx - lastSpace > 55) {
						Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 352 + offsetY * 12, quest->getDescription().substr(lastSpace, idx - lastSpace).c_str(), white, true);
						lastSpace = idx;
						offsetY++;

					}
				}
				idx++;
			}
		} else {
			Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 352, "???", white, true);
		}

		//copy screen
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}

}

/**************************
 *    DRAW GAME OPTION MENU
 *************************/
void Hammerfest::drawGameOptionSoloMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 30, "GAME OPTION SOLO", red, true);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 70, "Jouez la vraie Aventure ! Liberez les fruits !", white, true);
		for (int i = 0; i < 5; i++) {
			if (GameConfig::Instance().getSoloOptionUnlock(i)) {
				if (GameConfig::Instance().getSoloOption(i)) {
					copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 1), screenBuffer, 107, 147 + (60 * i));
				} else {
					copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 0), screenBuffer, 107, 147 + (60 * i));
				}
			} else {
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 2), screenBuffer, 107, 147 + (60 * i));
			}
		}
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 147, "Miroir", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 207, "Cauchemar", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 267, "Ninjutsu", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 327, "Explosifs instables", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 387, "Tornade", red, false);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 75, 147 + cursorPosition * 60);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

void Hammerfest::drawGameOptionLearningMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 30, "GAME OPTION APRENTISSAGE", red, true);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 70, "Apprenez a jouer en quelques minutes !", white, true);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

void Hammerfest::drawGameOptionMultiMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 30, "GAME OPTION MULTI", red, true);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 70, "Le mode Aventure pour 2 joueurs ! Jouez avec un ami !", white, true);
		for (int i = 0; i < 3; i++) {
			if (GameConfig::Instance().getMultiOptionUnlock(i)) {
				if (GameConfig::Instance().getMultiOption(i)) {
					copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 1), screenBuffer, 107, 147 + (60 * i));
				} else {
					copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 0), screenBuffer, 107, 147 + (60 * i));
				}
			} else {
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 2), screenBuffer, 107, 147 + (60 * i));
			}
		}
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 147, "Miroir", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 207, "Cauchemar", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 267, "Partage de vies", red, false);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 75, 147 + cursorPosition * 60);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

void Hammerfest::drawGameOptionTimeAttackMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 30, "GAME OPTION TIME ATTACK", red, true);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 70, "Affrontez le defi du temps ! Finissez le 6 niveaux dans le moins", white, true);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 85, "de temps possible. Ici, pas de place au hasard ! Tout doit etre", white, true);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 100, "calcule au millimetre pres pour assurer un chrono imbattable.", white, true);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

void Hammerfest::drawGameOptionSoccerMenu() {
	if (redrawMenu) {
		fillScreenBufferWithSurface("menu_background_2", 0);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 210, 30, "GAME OPTION SOCCER", red, true);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 70, "Ce mode est pour 2 joueurs. Jouez au foot contre un ami !", white, true);
		Text::Instance().drawText(screenBuffer, "verdana10pt10", 210, 85, "Choississez le niveau :", white, true);

		//controle avancé
		if (GameConfig::Instance().isKickcontrolUnlock()) {
			if (GameConfig::Instance().getSoccerOption(0)) {
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 1), screenBuffer, 107, 147);
			} else {
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 0), screenBuffer, 107, 147);
			}
		} else {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 2), screenBuffer, 107, 147);
		}
		//bombes
		if (GameConfig::Instance().getSoccerOption(1)) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 1), screenBuffer, 107, 207);
		} else {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_checkbox", 0), screenBuffer, 107, 207);
		}

		for (int i = 0; i < 4; i++) {
			if (GameConfig::Instance().getSoccerMap() == i) {
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_radio", 0), screenBuffer, 107, 267 + (60 * i));
			} else {
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_game_radio", 1), screenBuffer, 107, 267 + (60 * i));
			}
		}
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 147, "Controles avances", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 207, "Bombes", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 267, "gazon maudit", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 327, "temple du ballon", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 387, "volleyfest", red, false);
		Text::Instance().drawText(screenBuffer, "verdanaBold20", 170, 447, "maitrise aerienne", red, false);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("menu_cursor", 0), screenBuffer, 75, 147 + cursorPosition * 60);
		copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
		redrawMenu = false;
	}
}

//ItemFileSystem::Instance().loadAccount(0);
//ItemFileSystem::Instance().simulateGame();
//ItemFileSystem::Instance().save(4400000, true, 110);

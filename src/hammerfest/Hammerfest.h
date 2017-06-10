#include <SDL2/SDL.h>
#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>
#else
#include <SDL2_image/SDL_image.h>
#include <SDL2_gfx/SDL2_rotozoom.h>
#endif
#include <stdio.h>
#include <sstream>

#include "utils/Sound.h"
#include "utils/Sprite.h"
#include "utils/GameConfig.h"
#include "item/ItemFileSystem.h"

#ifndef __MYCLASS_HAMMERFEST
#define __MYCLASS_HAMMERFEST
class Hammerfest {

	public:
		Hammerfest(SDL_Surface * vout_bufLibretro, char * saveFilePath, bool newSaveFile);
		~Hammerfest();
		void tick(unsigned short in_keystateLibretro[16]);
	private:
		//get key pressed on gamepad
		void keyPressed();

		//draw screen
		void drawSplashScreen();
		void drawSaveGameMenu();
		void drawMainMenu();
		void drawGameModeMenu();
		void drawFridgeMenu();
		void drawQuestMenu();
		void drawGameOptionSoloMenu();
		void drawGameOptionMultiMenu();
		void drawGameOptionTimeAttackMenu();
		void drawGameOptionSoccerMenu();

		//buffer for draw
		SDL_Surface *screenBuffer;
		SDL_Surface * vout_buf;

		//what menu to draw
		int drawMenu;
		int drawNextMenu;
		bool redrawMenu;

		int fridgeItemPosition;
		int fridgeFirstItemView;

		int questSelect;
		int firstQuestView;

		//color mask
		Uint32 rmask, gmask, bmask, amask;

		//keystate
		unsigned short in_keystate[16];
		bool keychange[16];
		bool anyPlayerkeychange;
		unsigned short previousPlayerKeystate[16];

		//utils
		void copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y);
		void fillScreenBufferWithSurface(std::string name, int index);
};
#endif

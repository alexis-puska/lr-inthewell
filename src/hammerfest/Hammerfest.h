#include <SDL2/SDL.h>
#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif
#include <stdio.h>
#include "utils/Sound.h"
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
		void drawGameModeMenu();
		void drawGameOptionMenu();
		void drawFridgeMenu();
		void drawQuestMenu();

		//buffer for draw
		SDL_Surface *screenBuffer;
		SDL_Surface * vout_buf;

		//what menu to draw
		int drawMenu;

		//keystate
		unsigned short in_keystate[16];
		bool keychange[16];
		bool anyPlayerkeychange;
		unsigned short previousPlayerKeystate[16];

		//utils
		void copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y);
};
#endif

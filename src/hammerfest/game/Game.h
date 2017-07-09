#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>


#ifndef __MYCLASS_GAME
#define __MYCLASS_GAME

#include "../utils/Sound.h"
#include "../utils/Sprite.h"
#include "../utils/LevelService.h"
#include "../level/Level.h"

#define gameTick 25

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

enum gameStateEnum {
	gameStart = 0, gamePause = 1, gameEnd = 2, gameShowMap = 3
};

class Game {

	public:
		Game();
		Game(SDL_Surface * vout_buf, unsigned short * in_keystate);
		~Game();
		void tick();
		bool isConfigured();
		bool isAlive();
		bool isRequestStopGame();
		void startGame();
		void exitGame();
		void stopGame();
	private:
		/************************
		 * VARIABLES FOR THREAD
		 ************************/
		//Thread variable
		bool configured;
		bool isThreadAlive;
		bool requestStopGame;
		SDL_Thread * mainThread;
		//pointer in the libretro buffer
		SDL_Surface * vout_buf;
		int gameState;
		Uint32 rmask, gmask, bmask, amask;
		//keystate of player
		unsigned short * in_keystate;
		SDL_Surface * screenBuffer;

		Level * currentLevel;

		int count,idx;

		/************************
		 * FUNCTION
		 ************************/
		void copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y);
		void fillScreenBufferWithSurface(std::string name, int index, SDL_Surface * destination);
		void mergeScreen();
};
#endif

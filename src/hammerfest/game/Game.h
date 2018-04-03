#ifdef IS_OSX
#include <SDL2_image/SDL_image.h>
#elif WIN32
#include <SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include <iostream>
#include <vector>
#include <algorithm>

#ifndef __MYCLASS_GAME
#define __MYCLASS_GAME

#include "../utils/Sound.h"
#include "../utils/Sprite.h"
#include "../utils/Text.h"
#include "../utils/LevelService.h"
#include "../level/Level.h"
#include "Player.h"

#define gameTick 25
#define startLevelIndex 4

enum gameStateEnum
{
	gameStart = 0,
	gamePause = 1,
	gameEnd = 2,
	gameShowMap = 3,
	gameChangeLevel = 4
};

enum changeLevelEnum
{
	changeLevelImmediat = 0,
	changeLevelToRight = 1,
	changeLevelToLeft = 2,
	changeLevelNormal = 3
};

class Game
{

  public:
	Game();
	Game(SDL_Surface *vout_buf, unsigned short *in_keystate);
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
	SDL_Thread *mainThread;
	//pointer in the libretro buffer
	SDL_Surface *vout_buf;
	int gameState;

	//keystate of player
	unsigned short *in_keystate;
	SDL_Surface *screenBuffer;
	SDL_Surface *darknessBuffer;

	Level *currentLevel;

	SDL_Surface *pauseGameBuffer;

	std::vector<Player *> players;
	std::vector<Ennemie *> ennemies;

	//numero du niveau courant
	int idx;

	//changement de niveau
	int changeLevelAnimationPosition;
	int changeLevelAnimationType;
	SDL_Surface *changeLevelBufferAnimationVertical;
	SDL_Surface *changeLevelBufferAnimationHorizontal;

	bool bossMusic;
	bool releaseButton;

	/************************
		 * FUNCTION
		 ************************/
	void copySurfaceToBackRenderer(SDL_Surface *src, SDL_Surface *dest, int x, int y);
	void copySurfaceToBackRendererWithStartOffset(SDL_Surface *src, SDL_Surface *dest, int x, int y, int lengthX, int lengthY, int offsetX,
												  int offsetY);
	void fillScreenBufferWithSurface(std::string name, int index, SDL_Surface *destination);
	void mergeScoreAndBorder();
	void generateDarkness();
	void excludeDarkness(int posX, int posY, double zoom);

	void drawChangeLevel();

	void drawLevelBackground();
	void drawLevelForeground();
	void drawPauseScreen();
	void drawMapScreen();
};
#endif

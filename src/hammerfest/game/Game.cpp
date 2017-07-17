#include "Game.h"

/***********************************************
 *               TICK generator
 ***********************************************/
static int metronome(void* data) {
	Game *game = ((Game *) data);
	struct timeval t1, t2;
	long delay;
	long warningCount = 0l;
	while (game->isAlive()) {
		gettimeofday(&t1, NULL);
		game->tick();
		gettimeofday(&t2, NULL);

		long milliseconds = (t2.tv_usec - t1.tv_usec) / 1000;
		if (milliseconds < 0) {
			milliseconds += 1000;
		}

		delay = gameTick - milliseconds;
		if (delay > 0) {
			if (delay < 5) {
				warningCount++;
				fprintf(stderr, "%i ms %li\n", (int) delay, warningCount);
			}
			fprintf(stderr,"d%li\n",delay);
			SDL_Delay(delay);
		} else {
			warningCount++;
			fprintf(stderr, "warning %li\n", warningCount);
		}
	}
	return 0;
}

/***********************************************
 *             Default constructor
 ***********************************************/
Game::Game() {
	srand (time(NULL));amask = 0xff000000;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
	gameState = gameStart;
	isThreadAlive = false;
	configured = false;
	requestStopGame = false;
	idx = 0;
}

/**********************************************
 *                 Constructor
 **********************************************/
Game::Game(SDL_Surface * vout_buf, unsigned short * in_keystate) {
	srand (time(NULL));amask
	= 0xff000000;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
	this->vout_buf = vout_buf;
	this->in_keystate = in_keystate;
	isThreadAlive = false;
	configured = true;
	requestStopGame = false;
	currentLevel = LevelService::Instance().getLevel(0);
	currentLevel->generateBackGround(-1);
	idx = 0;
	startGame();
}

/**********************************************
 *                  Destructor
 **********************************************/
Game::~Game() {
	exitGame();
	in_keystate = NULL;
	vout_buf = NULL;
	SDL_FreeSurface(screenBuffer);
}

/**********************************************
 * function to copy a surface inside an other.
 **********************************************/
void Game::copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y) {
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

/*******************************************
 * fill surface with another surface
 *******************************************/
void Game::fillScreenBufferWithSurface(std::string name, int index, SDL_Surface * destination) {
	SDL_Surface * temp2 = Sprite::Instance().getAnimation(name, index);
	int x = 0;
	int y = 0;
	while (y < 500) {
		while (x < 420) {
			copySurfaceToBackRenderer(temp2, destination, x, y);
			x += temp2->w;
		}
		x = 0;
		y += temp2->h;
	}
}

bool Game::isConfigured() {
	return configured;
}

bool Game::isAlive() {
	return isThreadAlive;
}

bool Game::isRequestStopGame() {
	return requestStopGame;
}

/*******************************************
 * merge all surface of a screen
 * - background + platform
 * - ennemies + players
 * - darkness and score
 *******************************************/
void Game::mergeScreen() {
	if (currentLevel->getId() != 0) {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_left", 0), screenBuffer, 0, 0);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_right", 0), screenBuffer, 404, 0);
	}
	copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_score", 0), screenBuffer, 0, 500);
	copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
}

/*******************************************
 * function that initialise totaly a game
 *******************************************/
void Game::startGame() {
	Sound::Instance().stopMusique();
	Sound::Instance().startMusic();
	if (!isThreadAlive) {
		isThreadAlive = true;
		idx = 0;
		mainThread = SDL_CreateThread(metronome, "mainThread", this);
	}

}

/*******************************************
 * function to kill the main thread
 *******************************************/
void Game::stopGame() {
	if (isThreadAlive) {
		Sound::Instance().stopMusique();
		Sound::Instance().startMusicBoss();
		isThreadAlive = false;
		configured = false;
		requestStopGame = false;
		int treadResult = 0;
		SDL_WaitThread(mainThread, &treadResult);
		fprintf(stderr, "result stop thread %i\n", treadResult);
	}
}

/*******************************************
 * function to exit Game
 *******************************************/
void Game::exitGame() {
	stopGame();
}

/*******************************************
 *           main function of game
 *******************************************/
void Game::tick() {

	//START TEMPORARY LINE
	if (in_keystate[0] & keyPadSelect && !requestStopGame) {
		requestStopGame = true;
	} else if (in_keystate[0] & keyPadUp && !requestStopGame) {
		idx--;
		if (idx < 0) {
			idx = 103;
		}
		currentLevel = LevelService::Instance().getLevel(idx);
		currentLevel->generateBackGround(-1);
	} else if (in_keystate[0] & keyPadDown && !requestStopGame) {
		idx++;
		if (idx > 103) {
			idx = 0;
		}
		currentLevel = LevelService::Instance().getLevel(idx);
		currentLevel->generateBackGround(-1);
	}
	//END TEMPORARY LINE



	//getBackGround
	copySurfaceToBackRenderer(currentLevel->getBackground(), screenBuffer, 0, 0);

	//draw all Element of the level. (Vortex, teleporter, rayon...)
	currentLevel->drawHimself(screenBuffer);

	//Draw Player

	//Draw Ennemies

	//Draw Foreground Decor
	currentLevel->drawForeGroundElement(screenBuffer);

	//Copy the generate image to the buffer to retroarch
	mergeScreen();
}

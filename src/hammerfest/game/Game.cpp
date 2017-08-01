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
				//fprintf(stderr, "%i ms %li\n", (int) delay, warningCount);
			}
			//fprintf(stderr, "d%li\n", delay);
			SDL_Delay(delay);
		} else {
			warningCount++;
			//fprintf(stderr, "warning %li %li\n", warningCount, delay);
		}
	}
	return 0;
}

/***********************************************
 *             Default constructor
 ***********************************************/
Game::Game() {
	srand (time(NULL));Uint32 rmask, gmask, bmask, amask;
	amask = 0xff000000;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
	darknessBuffer = SDL_CreateRGBSurface(0, 420, 500, 32, rmask, gmask, bmask, amask);
	previousLevelBuffer = SDL_CreateRGBSurface(0, 420, 500, 32, rmask, gmask, bmask, amask);
	gameState = gameStart;
	isThreadAlive = false;
	configured = false;
	requestStopGame = false;
	changeLevelAnimationPosition = 0;
	idx = 0;
}

/**********************************************
 *                 Constructor
 **********************************************/
Game::Game(SDL_Surface * vout_buf, unsigned short * in_keystate) {
	srand (time(NULL));Uint32 rmask, gmask, bmask, amask;
	amask = 0xff000000;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
	darknessBuffer = SDL_CreateRGBSurface(0, 420, 500, 32, rmask, gmask, bmask, amask);
	previousLevelBuffer = SDL_CreateRGBSurface(0, 420, 500, 32, rmask, gmask, bmask, amask);
	this->vout_buf = vout_buf;
	this->in_keystate = in_keystate;
	isThreadAlive = false;
	configured = true;
	requestStopGame = false;
	currentLevel = LevelService::Instance().getLevel(0);
	currentLevel->generateBackGround(-1);
	ennemies = currentLevel->getEnnemiesList();
	players.push_back(new Player(100,100,0,&in_keystate[0]));
	idx = 0;
	changeLevelAnimationPosition = 0;
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
	SDL_FreeSurface(darknessBuffer);
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
		//fprintf(stderr, "result stop thread %i\n", treadResult);
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
		//TODO pause
	} else if (in_keystate[0] & keyPadStart && !requestStopGame) {
		//TODO Map
	} else if (in_keystate[0] & keyPadL1 && !requestStopGame) {
		idx--;
		if (idx < 0) {
			idx = 103;
		}
		currentLevel = LevelService::Instance().getLevel(idx);
		currentLevel->generateBackGround(-1);
		ennemies = currentLevel->getEnnemiesList();
	} else if (in_keystate[0] & keyPadR1 && !requestStopGame) {
		idx++;
		if (idx > 103) {
			idx = 0;
		}
		currentLevel = LevelService::Instance().getLevel(idx);
		currentLevel->generateBackGround(-1);
		ennemies = currentLevel->getEnnemiesList();
	}
	//END TEMPORARY LINE

	if (currentLevel->getId() > 15) {
		generateDarkness();
	}

	//getBackGround
	copySurfaceToBackRenderer(currentLevel->getBackground(), screenBuffer, 0, 0);

	//draw all Element of the level. (Vortex, teleporter, rayon...)
	currentLevel->drawHimself(screenBuffer);

	//TODO
	//Draw Player
	for (unsigned int i = 0; i < players.size(); i++) {
		players[i]->doSomething(screenBuffer, currentLevel->getPlatformGrid());
	}

	//TODO
	//Draw Ennemies
	for (unsigned int i = 0; i < ennemies.size(); i++) {
		ennemies[i]->doSomething(screenBuffer);
	}

	//merge score and left/right border before the foreground decor for level1
	if (currentLevel->getId() == 1) {
		mergeScoreAndBorder();
		currentLevel->drawForeGroundElement(screenBuffer);
	} else {
		currentLevel->drawForeGroundElement(screenBuffer);
		mergeScoreAndBorder();
	}

	//merge darkness
	if (currentLevel->getId() > 15) {
		excludeDarkness(0, 0, 1.0);
		excludeDarkness(250, 250, 1.0);
		excludeDarkness(420, 500, 0.5);
		excludeDarkness(420, 0, 3.0);

		copySurfaceToBackRenderer(darknessBuffer, screenBuffer, 0, 0);
	}
	//Copy the generate image to the buffer to retroarch
	copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
}

/*******************************************
 *   merge score and border
 ******************************************/
void Game::mergeScoreAndBorder() {
	if (currentLevel->getId() != 0) {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_left", 0), screenBuffer, 0, 0);
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_right", 0), screenBuffer, 404, 0);
	}
	copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_score", 0), screenBuffer, 0, 500);
}

/*******************************************
 *
 *   ----------DARKNESS----------
 *
 ******************************************/
void Game::generateDarkness() {
	int darknessValue = ceil((float) (255 / 85) * (float) (currentLevel->getId() - 15));
	if (darknessValue >= 255) {
		darknessValue = 255;
	}
	SDL_FillRect(darknessBuffer, NULL, SDL_MapRGBA(darknessBuffer->format, 0, 0, 0, darknessValue));
}

void Game::excludeDarkness(int in_X, int in_Y, double zoom) {
	if (darknessBuffer != NULL) {
		SDL_Surface * temp = rotozoomSurfaceXY(Sprite::Instance().getAnimation("shadow", 0), 0, zoom, zoom, 0);

		const int halfWidth = temp->w / 2;
		const int halfHeight = temp->h / 2;

		SDL_Rect sourceRect = { 0, 0, temp->w, temp->h };
		SDL_Rect destRect = { in_X - halfWidth, in_Y - halfHeight, temp->w, temp->h };

		// Make sure our rects stays within bounds
		if (destRect.x < 0) {
			sourceRect.x -= destRect.x; // remove the pixels outside of the surface
			sourceRect.w -= sourceRect.x; // shrink to the surface, not to offset fog
			destRect.x = 0;
			destRect.w -= sourceRect.x; // shrink the width to stay within bounds
		}
		if (destRect.y < 0) {
			sourceRect.y -= destRect.y; // remove the pixels outside
			sourceRect.h -= sourceRect.y; // shrink to the surface, not to offset fog
			destRect.y = 0;
			destRect.h -= sourceRect.y; // shrink the height to stay within bounds
		}

		int xDistanceFromEdge = (destRect.x + destRect.w) - darknessBuffer->w;
		if (xDistanceFromEdge > 0) {
			// we're busting
			sourceRect.w -= xDistanceFromEdge;
			destRect.w -= xDistanceFromEdge;
		}
		int yDistanceFromEdge = (destRect.y + destRect.h) - darknessBuffer->h;
		if (yDistanceFromEdge > 0) {
			// we're busting
			sourceRect.h -= yDistanceFromEdge;
			destRect.h -= yDistanceFromEdge;
		}

		SDL_LockSurface(darknessBuffer);

		Uint32* destPixels = (Uint32*) darknessBuffer->pixels;
		Uint32* srcPixels = (Uint32*) temp->pixels;
		for (int x = 0; x < destRect.w; ++x) {
			for (int y = 0; y < destRect.h; ++y) {
				Uint32* destPixel = destPixels + (y + destRect.y) * darknessBuffer->w + destRect.x + x;
				Uint32* srcPixel = srcPixels + (y + sourceRect.y) * temp->w + sourceRect.x + x;
				unsigned char* destAlpha = (unsigned char*) destPixel + 3; // fetch alpha channel
				unsigned char* srcAlpha = (unsigned char*) srcPixel + 3; // fetch alpha channel
				if (*destAlpha > *srcAlpha) {
					*destAlpha = *srcAlpha;
				}
			}
		}
		SDL_UnlockSurface(darknessBuffer);
		SDL_FreeSurface(temp);
	}
}

/*******************************************
 *
 * -------- LEVEL CHANGE ANIMATION --------
 *
 ******************************************/
void Game::drawChangeLevel() {

}

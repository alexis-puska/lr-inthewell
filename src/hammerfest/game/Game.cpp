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
	count = 0;
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
	count = 0;
	idx = 0;
	vortex = new Vortex(1, 32, 64, 0.5, 1, true, 5);
	platform = new Platform(1, 10, 10, true, true, 4, 51);
	door = new Door(1, 90, 90, 3, true, 1, 1, NULL);
	pick = new Pick(1, 11, 11, true, pickToRight);
	rayon = new Rayon(12, 12, 5, 6, false);
	teleporter = new Teleporter(1, 13, 13, 5, false, 1);
	startGame();
}

/**********************************************
 *                  Destructor
 **********************************************/
Game::~Game() {
	exitGame();
	in_keystate = NULL;
	vout_buf = NULL;
	delete vortex;
	delete platform;
	delete door;
	delete pick;
	delete rayon;
	delete teleporter;
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
//	SDL_Rect mergeRect;
//	mergeRect.x = 0;
//	mergeRect.y = 0;
//	mergeRect.w = 420;
//	mergeRect.h = 520;
	//SDL_BlitSurface(grid->getGroundLayer(), &mergeRect, screenBuffer, &mergeRect);
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
	if (in_keystate[0] & keyPadSelect && !requestStopGame) {
		requestStopGame = true;
	}

	if (screenBuffer == NULL) {
		screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
	}

	fillScreenBufferWithSurface("level_background", idx, screenBuffer);
	count++;
	if (count > 20) {
		idx++;
		count = 0;
	}
	if (idx >= 27) {
		idx = 0;
	}

	//fprintf(stderr,"vortex\n");
	vortex->drawHimself(screenBuffer);
	//fprintf(stderr,"platform\n");
	platform->drawHimself(screenBuffer);
	//fprintf(stderr,"door\n");
	door->drawHimself(screenBuffer);
	//fprintf(stderr,"pick\n");
	pick->drawHimself(screenBuffer);
	//fprintf(stderr,"rayon\n");
	rayon->drawHimself(screenBuffer);
	//fprintf(stderr,"teleporter\n");
	teleporter->drawHimself(screenBuffer);
	//fprintf(stderr,"merge\n");
	mergeScreen();
}

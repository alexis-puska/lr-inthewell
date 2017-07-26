#ifndef __MYCLASS_PLAYER
#define __MYCLASS_PLAYER

#include "../definition/Position.h"
#include "../definition/Drawable.h"
#include "../utils/Sound.h"

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

enum playerState {
	playerWait = 0,
	playerWalk = 1,
	playerJump = 2,
	playerStartFall = 3,
	playerFall = 4,
	playerLanding = 5,
	playerKill = 6,
	playerDead = 7,
	playerShot = 8,
	playerDrop = 9,
	playerBorder = 10,
	playerBoring = 11,
	playerChewingGum = 12,
	playerKnockOut = 13,
	playerRaiseUp = 14,
	playerRespawn = 15,
	playerRun = 16,
	playerCry = 17

};

enum playerDirection {
	playerDontMove = 0, playerGoLeft = 1, playerGoRight = 2
};

class Player: public Position, Drawable {
	public:
		Player(int x, int y, int type, unsigned short * in_keystate);
		~Player();
		void doSomething(SDL_Surface * dest);
	private:
		int type; //O - igor, 1 - Sandy
		unsigned short * in_keystate;


		int state;
		bool playerCanRun;


		bool shotBombe;
		bool shotBombeUpper;


		int jumpCyclePosition;
		int fallCyclePosition;
		bool playerFalling;

		int previousDirection;
		int direction;
		int animIdx;
		int animIdxMax;

		void changeState(int newState);
};
#endif

#ifndef __MYCLASS_PLAYER
#define __MYCLASS_PLAYER

#include "../definition/Position.h"
#include "../definition/Drawable.h"

class Player: public Position, Drawable {
	public:
		Player(int x, int y, int type);
		~Player();
		void doSomething(SDL_Surface * dest);
	private:
		int type; //O - igor, 1 - Sandy
};
#endif

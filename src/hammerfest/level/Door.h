#ifndef __MYCLASS_DOOR
#define __MYCLASS_DOOR

#include "../definition/Position.h"
#include "../definition/Drawable.h"
#include "Lock.h"

#define doorHitboxBorder 5

class Door: public Position, Drawable, HitBox {
	public:
		Door(int x, int y, int type, bool locked, int toLevel, int requieredKey, Lock * lock);
		~Door();
		bool isLocked();
		void unlock();
		void checkToUnlock(/*PlayerPosition TODO*/);
		int getDestination();
		void drawHimself(SDL_Surface * dest);
	private:
		int type;
		bool locked;
		int toLevel;
		int requieredKey;
		Lock * lock;
};
#endif

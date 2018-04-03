#ifndef __MYCLASS_DOOR
#define __MYCLASS_DOOR

#include "../definition/Position.h"
#include "../definition/Drawable.h"
#include "../definition/IdElement.h"
#include "Lock.h"

#define doorHitboxBorder 5

class Door : public Position, public Drawable, public HitBox, public IdElement
{
  public:
	Door(int id, int x, int y, int type, bool locked, int toLevel, int requieredKey, Lock *lock);
	~Door();
	bool isLocked();
	void unlock();
	void checkToUnlock(/*PlayerPosition TODO*/);
	int getDestination();
	void drawHimself(SDL_Surface *dest);

  private:
	int type;
	bool locked;
	int toLevel;
	int requieredKey;
	Lock *lock;
};
#endif

#include "../item/ItemFileSystem.h"

#ifndef __MYCLASS_LOCK
#define __MYCLASS_LOCK

#include "../definition/Position.h"
#include "../definition/Drawable.h"
#include "../definition/HitBox.h"

#define lockHitboxBorder 5

class Lock : public Drawable, public Position, public HitBox, public IdElement
{
  public:
	Lock(int id, int x, int y, int requieredKeyId);
	~Lock();
	bool isLocked();
	void checkToUnlock(/*PlayerPosition TODO*/);
	void drawHimself(SDL_Surface *dest);

  private:
	bool locked;
	int requieredKey;
};
#endif

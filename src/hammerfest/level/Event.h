#ifndef __MYCLASS_EVENT
#define __MYCLASS_EVENT

#include "../definition/Position.h"
#include "Door.h"

class Event : public Position{
	public:

	private:
		bool byBombe;
		bool byPlayer;
		bool afterAllEnemiesKilled;
		int objectId;
		int vortex;
		int animation;
		Door * doorToUnlock;
		Position * piece;
};

#endif

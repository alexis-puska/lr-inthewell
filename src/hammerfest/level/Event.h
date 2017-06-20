#ifndef __MYCLASS_EVENT
#define __MYCLASS_EVENT

#include "../definition/Position.h"
#include "Door.h"
#include "Vortex.h"

class Event : public Position{
	public:

	private:
		bool byBombe;
		bool byPlayer;
		bool afterAllEnemiesKilled;
		int objectId;
		Vortex * vortex;
		std::string animation;
		Door * doorToUnlock;
		Position * piece;
};

#endif

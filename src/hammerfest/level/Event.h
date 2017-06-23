#ifndef __MYCLASS_EVENT
#define __MYCLASS_EVENT

#include "../definition/Position.h"
#include "../definition/IdElement.h"
#include "../game/Game.h"

enum eventTriggerTypeEnum{
	triggerByBombe = 0,
	triggerByPlayer,
	triggerWhenNoEnnemies
};


class Event: public Position, public IdElement {
	public:
		Event(int id, int x, int y, bool triggered, int type, int objectId, int vortexId, std::string animation, int doorsId, int plateformToRemove,
				int plateformToMove, int movePlateformX, int movePlateformY);
		~Event();
		void doSomething(Game * game);
	private:
		bool triggered;
		int type;
		int objectId;
		int vortexId;
		std::string animation;
		int doorsId;
		int plateformToRemove;
		int plateformToMove;
		int movePlateformX;
		int movePlateformY;

		void CheckBombes() ;
		void CheckPlayerPosition();
		void CheckEnnemiesKilled();
};

#endif

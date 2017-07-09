#include "Event.h"

Event::Event(int id, int x, int y, int type, int objectId, int vortexId, std::string animation, int doorsId, int plateformToRemove, int plateformToMove, int movePlateformX, int movePlateformY) :
		Position(x, y), IdElement(id) {
	this->type = type;
	this->objectId = objectId;
	this->vortexId = vortexId;
	this->animation = animation;
	this->doorsId = doorsId;
	this->plateformToRemove = plateformToRemove;
	this->plateformToMove = plateformToMove;
	this->movePlateformX = movePlateformX;
	this->movePlateformY = movePlateformY;
}

Event::~Event() {

}

void Event::doSomething() {
	if (!triggered) {
		switch (type) {
			case triggerByBombe:
				CheckBombes();
				break;
			case triggerByPlayer:
				CheckPlayerPosition();
				break;
			case triggerWhenNoEnnemies:
				CheckEnnemiesKilled();
				break;
		}
		if (objectId != -1) {

		} else if (vortexId != -1) {

		} else if (!animation.empty()) {

		} else if (doorsId != -1) {

		} else if (plateformToRemove != -1) {

		} else if (plateformToMove != -1) {
			//movePlateformX
			//movePlateformY
		}
		triggered = true;
	}
}

void Event::CheckBombes() {

}

void Event::CheckPlayerPosition() {

}

void Event::CheckEnnemiesKilled() {

}

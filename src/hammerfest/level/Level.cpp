#include "Level.h"

Level::Level(int id, bool showPlatform, int backgroundId, int platformVerticalId, int platformHorizontalId){
	this->id = id;
	this->showPlatform = showPlatform;
	this->backgroundId = backgroundId;
	this->platformVerticalId = platformVerticalId;
	this->platformHorizontalId = platformHorizontalId;
}

int Level::getId() {
	return this->id;
}


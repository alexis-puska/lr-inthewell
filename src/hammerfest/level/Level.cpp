#include "Level.h"

Level::Level(int id, bool showPlatform, int backgroundId, int platformVerticalId, int platformHorizontalId) : IdElement(id){
	this->showPlatform = showPlatform;
	this->backgroundId = backgroundId;
	this->platformVerticalId = platformVerticalId;
	this->platformHorizontalId = platformHorizontalId;
}

Level::~Level(){

}

void Level::addDecor(Decor * decor) {
	decors[decor->getId()] = decor;
}

void Level::addPlatform(Platform * platform) {

}

void Level::addDoor(Door * door) {

}

void Level::addEvent(Event * event) {

}

void Level::addVortex(Vortex * vortex) {

}

void Level::AddTeleporter(Teleporter * teleporter) {

}

void Level::addRayons(Rayon * rayon) {

}

void Level::addStartPlayer(Position * startPlayer) {

}

void Level::addStartEffectObject(Position * startEffectObjet) {

}

void Level::addStartPointObject(Position * startPointObjet) {

}

void Level::addEnnemie(int x, int y, int type) {

}

/*********************************
 * 		UTIL FUNCTION
 *********************************/
void Level::removePlatform(int id) {

}

void Level::removeDeco(int id) {

}

/*********************************
 * 		GETTER FUNCTION
 *********************************/

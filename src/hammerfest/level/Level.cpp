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
	platforms[platform->getId()] = platform;
}

void Level::addDoor(Door * door) {
	doors[door->getId()] = door;
}

void Level::addEvent(Event * event) {
	events[event->getId()] = event;
}

void Level::addVortex(Vortex * vortex) {
	vortexs[vortex->getId()] = vortex;
}

void Level::AddTeleporter(Teleporter * teleporter) {
	teleporters[teleporter->getId()] = teleporter;
}

void Level::addRayons(Rayon * rayon) {
	rayons.push_back(rayon);
}

void Level::addStartPlayer(Position * startPlayer) {
	startPlayers.push_back(startPlayer);
}

void Level::addStartEffectObject(Position * startEffectObjet) {
	startEffectObjets.push_back(startEffectObjet);
}

void Level::addStartPointObject(Position * startPointObjet) {
	startPointObjets.push_back(startPointObjet);
}

void Level::addEnnemie(int x, int y, int type) {
	//ennemies
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

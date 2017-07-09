#include "Level.h"

Level::Level(int id, bool showPlatform, int backgroundId, int platformVerticalId, int platformHorizontalId, int next) :
		IdElement(id) {
	this->showPlatform = showPlatform;
	this->backgroundId = backgroundId;
	this->platformVerticalId = platformVerticalId;
	this->platformHorizontalId = platformHorizontalId;
	this->next = next;
}

Level::~Level() {
	decors.clear();
	platforms.clear();
	events.clear();
	doors.clear();
	vortexs.clear();
	teleporters.clear();
	rayons.clear();
	startPlayers.clear();
	startEffectObjets.clear();
	startPointObjets.clear();
	ennemies.clear();
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

void Level::drawHimself(SDL_Surface * dest){

}

void Level::drawHimself(SDL_Surface * backgroundBuffer, SDL_Surface * animBuffer, SDL_Surface * foregroundBuffer, SDL_Surface * shadowBuffer) {
	fprintf(stderr, "draw himself level : %i\n", id);
	fillScreenBufferWithSurface("level_background", backgroundId, backgroundBuffer);
	for (unsigned int i = 0; i < rayons.size(); i++) {
		rayons[i]->drawHimself(animBuffer);
	}
	for (std::map<int, Teleporter*>::iterator it = teleporters.begin(); it != teleporters.end(); ++it) {
		it->second->drawHimself(animBuffer);
	}
	for (std::map<int, Decor*>::iterator it = decors.begin(); it != decors.end(); ++it) {
		if(it->second->isOnBackground()){
			it->second->drawHimself(backgroundBuffer);
		}else{
			it->second->drawHimself(foregroundBuffer);
		}
	}

	for (std::map<int, Platform*>::iterator it = platforms.begin(); it != platforms.end(); ++it) {
		it->second->drawHimself(animBuffer);
	}


}

/*********************************
 * 		GETTER FUNCTION
 *********************************/

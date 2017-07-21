#include "Level.h"

Level::Level(int id, bool showPlatform, int backgroundId, int platformVerticalId, int platformHorizontalId, int next) :
		IdElement(id) {
	this->showPlatform = showPlatform;
	this->backgroundId = backgroundId;
	this->platformVerticalId = platformVerticalId;
	this->platformHorizontalId = platformHorizontalId;
	this->next = next;

	amask = 0xff000000;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	backgroundBuffer = SDL_CreateRGBSurface(0, 420, 500, 32, rmask, gmask, bmask, amask);
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
	SDL_FreeSurface(backgroundBuffer);
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

void Level::drawHimself(SDL_Surface * dest) {
	fprintf(stderr, "level : %i - ", id);
	for (unsigned int i = 0; i < rayons.size(); i++) {
		rayons[i]->drawHimself(dest);
	}
	for (std::map<int, Teleporter*>::iterator it = teleporters.begin(); it != teleporters.end(); ++it) {
		it->second->drawHimself(dest);
	}
}

void Level::deleteAreaInDarkness(SDL_Surface * darkness) {
	for (std::map<int, Decor*>::iterator it = decors.begin(); it != decors.end(); ++it) {
		if (it->second->getAnimation().compare("light") == 0) {
			//TODO
			//filledCircleRGBA(darkness, it->second->getX(), it->second->getY(), 59, 0, 0, 0, 0);
		}
	}
}

void Level::drawForeGroundElement(SDL_Surface * dest) {
	//draw decor in foreground.
	for (std::map<int, Decor*>::iterator it = decors.begin(); it != decors.end(); ++it) {
		if (!it->second->isOnBackground()) {
			it->second->drawHimself(dest);
		}
	}
}

void Level::generateBackGround(int backgroundEffect) {
	if (backgroundEffect != -1) {
		fillScreenBufferWithSurface("backgroundEffect", backgroundEffect, backgroundBuffer);
	} else {
		fillScreenBufferWithSurface("level_background", backgroundId, backgroundBuffer);
	}
	//draw platform on background (padding x=10 on the left)
	for (std::map<int, Platform*>::iterator it = platforms.begin(); it != platforms.end(); ++it) {
		it->second->drawHimself(backgroundBuffer);
	}
	//draw decor on background (must be draw without padding, start a X = 0)
	for (std::map<int, Decor*>::iterator it = decors.begin(); it != decors.end(); ++it) {
		if (it->second->isOnBackground()) {
			it->second->drawHimself(backgroundBuffer);
		}
	}
}

SDL_Surface * Level::getBackground() {
	return backgroundBuffer;
}

/*********************************
 * 		GETTER FUNCTION
 *********************************/

std::vector<Ennemie *> Level::getEnnemiesList(){
	return ennemies;
}

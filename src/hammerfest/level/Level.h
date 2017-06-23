#include <map>
#include <vector>
#include <stdio.h>

#ifndef __MYCLASS_LEVEL
#define __MYCLASS_LEVEL

#include "Door.h"
#include "Decor.h"
#include "Event.h"
#include "Ennemie.h"
#include "Vortex.h"
#include "Platform.h"
#include "Rayon.h"
#include "Teleporter.h"
#include "../definition/Position.h"

class Level {
	public:
		Level(int id, bool showPlatform, int backgroundId, int platformVerticalId, int platformHorizontalId);
		int getId();
	private:
		int id;
		bool showPlatform;
		int backgroundId;
		int platformVerticalId;
		int platformHorizontalId;
		std::map<int,Decor *> decors;
//		std::vector<Platform*> platforms;
//		std::vector<Event*> events;
//		std::vector<Door *> doors;
//		std::vector<Vortex *> vortex;
//		std::vector<Teleporter *> teleporters;
//		std::vector<Rayon *> rayons;
//		std::vector<Position *> startPlayer;
//		std::vector<Position *> startEffectObjet;
//		std::vector<Position *> startPointObjet;
//		std::vector<Ennemie *> ennemies;

};

#endif

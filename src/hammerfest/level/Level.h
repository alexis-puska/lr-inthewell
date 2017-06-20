#include <map>
#include <vector>
#include <stdio.h>

#ifndef __MYCLASS_LEVEL
#define __MYCLASS_LEVEL

#include "Door.h"
#include "Event.h"
#include "Vortex.h"
#include "Platform.h"
#include "Rayon.h"
#include "Teleporter.h"

class Level {
	public:

	private:
		int id;
		bool showPlatform;
		int backgroundId;
		int foregroundId;
		int platformVerticalId;
		int platformHorizontalId;
		std::vector<Platform*> platforms;
		std::vector<Event*> events;
		std::vector<Door *> doors;
		std::vector<Vortex *> vortex;
		std::vector<Teleporter *> teleporters;
		std::vector<Rayon *> rayons;
};

#endif

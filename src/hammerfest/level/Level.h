#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif

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
#include "../definition/IdElement.h"
#include "../definition/Drawable.h"

class Level: public IdElement, Drawable {
	public:
		Level(int id, bool showPlatform, int backgroundId, int platformVerticalId, int platformHorizontalId, int next);
		~Level();

		/*********************************
		 * 		BUILD FUNCTION
		 *********************************/

		void addDecor(Decor * decor);
		void addPlatform(Platform * platform);
		void addDoor(Door * door);
		void addEvent(Event * event);
		void addVortex(Vortex * vortex);
		void AddTeleporter(Teleporter * teleporter);
		void addRayons(Rayon * rayon);
		void addStartPlayer(Position * startPlayer);
		void addStartEffectObject(Position * startEffectObjet);
		void addStartPointObject(Position * startPointObjet);
		void addEnnemie(int x, int y, int type);

		/*********************************
		 * 		UTIL FUNCTION
		 *********************************/
		void removePlatform(int id);
		void removeDeco(int id);

		void deleteAreaInDarkness(SDL_Surface * darkness);
		void drawForeGroundElement(SDL_Surface * dest);

		void generateBackGround(int backgroundEffect);
		SDL_Surface * getBackground();

		void drawHimself(SDL_Surface * dest);

		std::vector<Ennemie *> getEnnemiesList();

	private:
		Uint32 rmask, gmask, bmask, amask;
		SDL_Surface * backgroundBuffer;

		bool showPlatform;
		int backgroundId;
		int platformVerticalId;
		int platformHorizontalId;
		int next;
		std::map<int, Decor *> decors;
		std::map<int, Platform*> platforms;
		std::map<int, Event*> events;
		std::map<int, Door *> doors;
		std::map<int, Vortex *> vortexs;
		std::map<int, Teleporter *> teleporters;
		std::vector<Rayon *> rayons;
		std::vector<Position *> startPlayers;
		std::vector<Position *> startEffectObjets;
		std::vector<Position *> startPointObjets;
		std::vector<Ennemie *> ennemies;
};

#endif

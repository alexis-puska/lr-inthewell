#ifndef __MYCLASS_TELEPORTER
#define __MYCLASS_TELEPORTER

#include "../definition/Position.h"
#include "../definition/IdElement.h"
#include "../definition/Drawable.h"
#include "../definition/HitBox.h"

#define gridSize 20
#define teleporterSpriteSize 94
#define bufferSize 7

class Teleporter: public Drawable, public Position, public HitBox, public IdElement {
	public:
		Teleporter(int id, int x, int y, int length, bool vertical, int toId);
		~Teleporter();
		void drawHimself(SDL_Surface * dest);
	private:
		int length;
		bool vertical;
		int toId;

		SDL_Surface * buffer;
		int offsetAnimation;
};
#endif

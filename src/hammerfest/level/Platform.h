#ifndef __MYCLASS_PLATFORM
#define __MYCLASS_PLATFORM

#include "../definition/Drawable.h"
#include "../definition/Position.h"
#include "../definition/IdElement.h"

#define gridSize 20

class Platform : public Drawable, public Position, public IdElement{
	public:
		Platform(int id, int x, int y, bool vertical, bool visible, int lenght, int surfaceId);
		~Platform();
		void drawHimself(SDL_Surface * surface);
	private:
		bool vertical;
		bool visible;
		int lenght;
		int surfaceId;
};
#endif

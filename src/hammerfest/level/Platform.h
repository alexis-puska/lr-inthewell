#ifndef __MYCLASS_PLATFORM
#define __MYCLASS_PLATFORM

#include "../definition/Drawable.h"
#include "../definition/Position.h"

class Platform : public Drawable, Position{
	public:
		Platform(int x, int y, bool vertical, bool visible, int lenght, int surfaceId);
		~Platform();
		void drawHimself(SDL_Surface * surface);
	private:
		bool vertical;
		bool visible;
		int lenght;
		int surfaceId;
};
#endif

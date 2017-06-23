#ifndef __MYCLASS_VORTEX
#define __MYCLASS_VORTEX

#include "../definition/Drawable.h"
#include "../definition/Position.h"
#include "../definition/HitBox.h"
#include "../definition/IdElement.h"

#define vortexHitboxBorder 5

class Vortex: public Drawable, public Position, public HitBox, public IdElement {
	public:
		Vortex(int id, int x, int y, double zoomX, double zoomY, bool enable, int destination);
		~Vortex();
		void enableVortex();
		bool isEnable();
		int getDestination();
		virtual void drawHimself(SDL_Surface * dest);
	private:
		float zoomX;
		float zoomY;
		bool enable;
		int destination;
		int animationPosition;
		std::vector<SDL_Surface *> animation;
};
#endif

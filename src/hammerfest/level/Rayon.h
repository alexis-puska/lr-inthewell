#ifndef __MYCLASS_RAYON
#define __MYCLASS_RAYON

#include "../definition/Drawable.h"
#include "../definition/HitBox.h"
#include "../definition/Position.h"

class Rayon : public Drawable, public Position, public HitBox{
	public:
		Rayon(int x, int y, int length, int type, bool vertical);
		~Rayon();
		int getType();
		void drawHimself(SDL_Surface * dest);
	private:
		int length;
		int type;
		bool vertical;
};
#endif
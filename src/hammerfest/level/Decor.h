#ifndef __MYCLASS_DECOR
#define __MYCLASS_DECOR

#include "../definition/Drawable.h"
#include "../definition/Position.h"

class Decor: public Drawable, Position {
	public:
		Decor(int id, int x, int y, bool displayed, bool background, std::string animation, int indexAnimation);
		~Decor();
		void display();
		bool isOnBackground();
		void drawHimself(SDL_Surface * destination);
	private:
		int id;
		bool displayed;
		bool background;
		std::string animation;
		int indexAnimation;
};
#endif

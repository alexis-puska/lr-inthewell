#ifndef __MYCLASS_PICK
#define __MYCLASS_PICK

#include "../definition/Drawable.h"
#include "../definition/HitBox.h"
#include "../definition/Position.h"
#include "../definition/IdElement.h"

#define gridSize 20

enum pickDirectionEnum{
	pickToTop = 0,
	pickToRight,
	pickToBottom,
	pickToLeft
};

class Pick : public Drawable, public Position, public IdElement, public HitBox{
	public:
		Pick(int id, int x, int y, bool visible, int direction);
		~Pick();
		void drawHimself(SDL_Surface * surface);
	private:
		int direction;
		bool visible;
};
#endif

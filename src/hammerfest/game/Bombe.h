#ifndef __MYCLASS_BOMBE
#define __MYCLASS_BOMBE

#include "../definition/Position.h"
#include "../definition/Drawable.h"

enum bombeTypeEnum{
	whiteBombe = 0,
	blueBombe,
	greenBombe,
	redBombe,
	blackBombe,
	kiwiBombe
};

class Bombe: public Position, Drawable {
	public:
		Bombe(int x, int y, int type);
		~Bombe();
	private:
		int type;
};
#endif

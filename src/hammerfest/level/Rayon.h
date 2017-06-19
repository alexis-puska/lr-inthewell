#ifndef __MYCLASS_RAYON
#define __MYCLASS_RAYON

#include "../definition/Drawable.h"

class Rayon : public Drawable{
	public:
		Rayon(int x, int y, int lenght, int giveBombeType);
	private:
		int lenght;
		int giveBombeType;
};
#endif

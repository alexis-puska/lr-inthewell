#include "Ennemie.h"

class Fraise : public Ennemie{
public:
	Fraise(int id, int x, int y);
	~Fraise();
	virtual void doSomething(SDL_Surface * dest);
};


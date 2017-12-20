#include "Ennemie.h"

class Framboise : public Ennemie{
public:
	Framboise(int id, int x, int y);
	~Framboise();
	virtual void doSomething(SDL_Surface * dest);
};


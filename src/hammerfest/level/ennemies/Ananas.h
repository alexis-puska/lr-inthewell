#include "Ennemie.h"

class Ananas : public Ennemie{
public:
	Ananas(int id, int x, int y);
	~Ananas();
	virtual void doSomething(SDL_Surface * dest);
};


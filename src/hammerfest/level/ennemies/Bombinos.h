#include "Ennemie.h"

class Bombinos : public Ennemie{
public:
	Bombinos(int id, int x, int y);
	~Bombinos();
	virtual void doSomething(SDL_Surface * dest);
};


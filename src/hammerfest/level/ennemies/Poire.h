#include "Ennemie.h"

class Poire : public Ennemie{
public:
	Poire(int id, int x, int y);
	~Poire();
	virtual void doSomething(SDL_Surface * dest);
};


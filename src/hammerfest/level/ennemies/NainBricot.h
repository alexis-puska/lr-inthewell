#include "Ennemie.h"

class NainBricot : public Ennemie{
public:
	NainBricot(int id, int x, int y);
	~NainBricot();
	virtual void doSomething(SDL_Surface * dest);
};


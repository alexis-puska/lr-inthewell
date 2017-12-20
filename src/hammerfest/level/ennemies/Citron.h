#include "Ennemie.h"

class Citron : public Ennemie{
public:
	Citron(int id, int x, int y);
	~Citron();
	virtual void doSomething(SDL_Surface * dest);
};


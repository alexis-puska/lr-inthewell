#include "Ennemie.h"

class Litchi : public Ennemie{
public:
	Litchi(int id, int x, int y);
	~Litchi();
	virtual void doSomething(SDL_Surface * dest);
};


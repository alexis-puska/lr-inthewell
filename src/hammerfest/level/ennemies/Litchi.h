#include "Ennemie.h"

class Litchi : public Ennemie{
public:
	Litchi(int id, int x, int y, Level * level);
	~Litchi();
	virtual void doSomething(SDL_Surface * dest);
};


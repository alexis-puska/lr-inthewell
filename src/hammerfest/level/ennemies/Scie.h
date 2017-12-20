#include "Ennemie.h"

class Scie : public Ennemie{
public:
	Scie(int id, int x, int y);
	~Scie();
	virtual void doSomething(SDL_Surface * dest);
};


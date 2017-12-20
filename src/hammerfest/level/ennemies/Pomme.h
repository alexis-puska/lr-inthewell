#include "Ennemie.h"

class Pomme : public Ennemie{
public:
	Pomme(int id, int x, int y);
	~Pomme();
	virtual void doSomething(SDL_Surface * dest);
};


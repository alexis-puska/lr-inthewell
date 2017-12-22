#include "Ennemie.h"

class Banane : public Ennemie{
public:
	Banane(int id, int x, int y, Level * level);
	~Banane();
	virtual void doSomething(SDL_Surface * dest);
};


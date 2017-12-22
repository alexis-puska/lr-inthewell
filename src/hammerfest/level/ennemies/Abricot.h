#include "Ennemie.h"

class Abricot : public Ennemie{
public:
	Abricot(int id, int x, int y, Level * level);
	~Abricot();
	virtual void doSomething(SDL_Surface * dest);
};


#include "Ennemie.h"

class Abricot : public Ennemie{
public:
	Abricot(int id, int x, int y);
	~Abricot();
	virtual void doSomething(SDL_Surface * dest);
};


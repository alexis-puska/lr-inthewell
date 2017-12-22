#include "Ennemie.h"

class Kiwi : public Ennemie{
public:
	Kiwi(int id, int x, int y, Level * level);
	~Kiwi();
	virtual void doSomething(SDL_Surface * dest);
};


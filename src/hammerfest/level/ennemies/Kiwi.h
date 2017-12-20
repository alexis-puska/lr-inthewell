#include "Ennemie.h"

class Kiwi : public Ennemie{
public:
	Kiwi(int id, int x, int y);
	~Kiwi();
	virtual void doSomething(SDL_Surface * dest);
};


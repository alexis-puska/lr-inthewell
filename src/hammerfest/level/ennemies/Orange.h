#include "Ennemie.h"

class Orange : public Ennemie{
public:
	Orange(int id, int x, int y, Level * level);
	~Orange();
	virtual void doSomething(SDL_Surface * dest);
};


#include "Ennemie.h"

class Pasteque : public Ennemie{
public:
	Pasteque(int id, int x, int y, Level * level);
	~Pasteque();
	virtual void doSomething(SDL_Surface * dest);
};


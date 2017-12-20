#include "Ennemie.h"

class Pasteque : public Ennemie{
public:
	Pasteque(int id, int x, int y);
	~Pasteque();
	virtual void doSomething(SDL_Surface * dest);
};


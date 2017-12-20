#include "Ennemie.h"

class Blob : public Ennemie{
public:
	Blob(int id, int x, int y);
	~Blob();
	virtual void doSomething(SDL_Surface * dest);
};


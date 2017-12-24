#include "Ennemie.h"

class Framboise : public Ennemie{
public:
	Framboise(int id, int x, int y, Level * level);
	~Framboise();
	virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
};


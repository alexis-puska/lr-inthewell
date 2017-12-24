#include "Ennemie.h"

class Ananas : public Ennemie{
public:
	Ananas(int id, int x, int y, Level * level);
	~Ananas();
	virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
};


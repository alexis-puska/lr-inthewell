#include "Ennemie.h"

class Scie : public Ennemie{
public:
	Scie(int id, int x, int y, Level * level);
	~Scie();
	virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
};


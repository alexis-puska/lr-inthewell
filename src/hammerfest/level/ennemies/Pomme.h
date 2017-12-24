#include "Ennemie.h"

class Pomme : public Ennemie{
public:
	Pomme(int id, int x, int y, Level * level);
	~Pomme();
	virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
};


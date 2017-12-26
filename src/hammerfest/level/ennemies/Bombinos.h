#include "Ennemie.h"

class Bombinos : public Ennemie{
public:
	Bombinos(int id, int x, int y, Level * level);
	~Bombinos();
	virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
    virtual void iMove();
};


#include "Ennemie.h"

class Citron : public Ennemie{
public:
	Citron(int id, int x, int y, Level * level);
	~Citron();
	virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
    virtual void iMove();
};


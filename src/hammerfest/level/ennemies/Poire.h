#include "Ennemie.h"

class Poire : public Ennemie
{
  public:
	Poire(int id, int x, int y, Level *level);
	~Poire();
	virtual void doSomething(SDL_Surface *dest, std::vector<Player *> players);
	virtual void iMove();
};

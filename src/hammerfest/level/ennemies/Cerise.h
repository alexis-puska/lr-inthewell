#include "Ennemie.h"

class Cerise : public Ennemie{
public:
    Cerise(int id, int x, int y, Level * level);
    ~Cerise();
    virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
    virtual void iMove();
};


#include "Ennemie.h"

class Blob : public Ennemie{
public:
    Blob(int id, int x, int y, Level * level);
    ~Blob();
    virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
    virtual void iMove();
};


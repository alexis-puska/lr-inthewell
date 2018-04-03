#include "Ennemie.h"

class Pasteque : public Ennemie
{
  public:
    Pasteque(int id, int x, int y, Level *level);
    ~Pasteque();
    virtual void doSomething(SDL_Surface *dest, std::vector<Player *> players);
    virtual void iMove();
    void movePasteque();
    void inverseDirectionX();
    void inverseDirectionY();
    bool toRight;
    bool toBottom;
    int lastInvX;
    int lastInvY;
};

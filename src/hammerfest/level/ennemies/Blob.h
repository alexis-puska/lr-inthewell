#include "Ennemie.h"

class Blob : public Ennemie
{
  public:
    Blob(int id, int x, int y, Level *level);
    ~Blob();
    virtual void doSomething(SDL_Surface *dest, std::vector<Player *> players);
    virtual void iMove();

  private:
    int direction;
    bool onTop;
    bool onLeft;
    bool onHorizontalBorder;
    bool onVerticalBorder;

    void adjustPosition();
    void drawBlob(SDL_Surface *sprite, SDL_Surface *dest);
};

#ifndef __MYCLASS_ENNEMIE
#define __MYCLASS_ENNEMIE

#include "../definition/Position.h"
#include "../definition/Drawable.h"
#include "../definition/IdElement.h"
#include "../definition/HitBox.h"

#define ennemieHitboxWidth 20
#define ennemieHitboxHeight 20

enum ennemieType {
    cerise	= 0,
    orange	= 1,
    pomme		= 2,
    banane	= 3,
    citron	= 4,
    bombinos	= 5,
    poire		= 6,
    abricot	= 7,
    litchi	= 8,
    fraise	= 9,
    kiwi		= 10,
    pasteque	= 11,
    ananas	= 12,
    blob		= 13,
    framboise	= 14,
    nainbricot	= 15,
};

class Ennemie : public Position, public Drawable, public HitBox, public IdElement {
public:
    Ennemie(int id, int x, int y, int type);
    ~Ennemie();
    void doSomething(SDL_Surface * dest);
private:
    int type;
    int animIdx;
    int animIdxMax;
};
#endif

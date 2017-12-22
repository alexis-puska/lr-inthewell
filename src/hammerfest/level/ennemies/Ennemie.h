#ifndef __MYCLASS_ENNEMIE
#define __MYCLASS_ENNEMIE

#include "../../definition/Position.h"
#include "../../definition/Drawable.h"
#include "../../definition/IdElement.h"
#include "../../definition/HitBox.h"


#define ennemieHitboxWidth 20
#define ennemieHitboxHeight 20

enum ennemieType {
	cerise = 0,
	orange = 1,
	pomme = 2,
	banane = 3,
	citron = 4,
	bombinos = 5,
	poire = 6,
	abricot = 7,
	litchi = 8,
	fraise = 9,
	kiwi = 10,
	pasteque = 11,
	ananas = 12,
	blob = 13,
	framboise = 14,
	nainbricot = 15,
	scie = 16
};

static const std::string ennemieTypeString[] = { "cerise", "orange", "pomme", "banane", "citron", 
"bombinos", "poire", "abricot", "litchi", "fraise", "kiwi", "pasteque", "ananas", "blob", "framboise", "nainbricot", "scie"};

enum ennemieState {
	walk = 0,
	angry,
	frozed,
	knock_out,
	knock_out2,
	dead,
	look_up,
	fall,
	look_left_right
};

static const std::string ennemieStateString[] = { "walk", "angry", "frozed","knock_out", "knock_out2", "dead", "look_up", "fall", "look_left_right" };

class Level;
class Ennemie : public Position, public Drawable, public HitBox, public IdElement {
public:
	Ennemie(int id, int x, int y, int type, Level * level);
	virtual ~Ennemie();
	virtual void doSomething(SDL_Surface * dest);
	void drawHimself(SDL_Surface * sprite, SDL_Surface * dest);
	std::string getStateString();
protected:
	int type;
	int animIdx;
	int animIdxMax;
	int state;
    Level *level;
};
#endif

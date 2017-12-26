#ifndef __MYCLASS_ENNEMIE
#define __MYCLASS_ENNEMIE

#include "../../definition/Position.h"
#include "../../definition/Drawable.h"
#include "../../definition/IdElement.h"
#include "../../definition/HitBox.h"
#include "../../game/Player.h"


#define ennemieHitboxWidth 20
#define ennemieHitboxHeight 20
#define ennemieSpeed 2
#define ennemieAngrySpeed 3

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
	dead,
    jump,
	look,
    shot
};

static const std::string ennemieStateString[] = { "walk", "angry", "frozed","knock_out", "dead", "look", "jump", "shot" };

enum ennemieDirection{
    left = 0,
    right,
    up,
    down
};

enum ennemieSituation {
	nothing = 0,
	bottomStairs,
	wall,
	topStaires,
	edge,
	edgeCanJump
};

class Level;
class Ennemie : public Position, public Drawable, public HitBox, public IdElement {
public:
	Ennemie(int id, int x, int y, int type, Level * level);
	virtual ~Ennemie();
	virtual void doSomething(SDL_Surface * dest, std::vector<Player *> players);
protected:
    int type;
	int animIdx;
	int animIdxMax;
	int state;
	int previousState;
    Level *level;
    int direction; //0: left, 1:right
    
    //fonction de déplacement
    virtual void iMove();
    void changeDirection();
    void move();
    
    //detection joueur/environnement
    bool plateformFrontMe();
    int whatITouch();
    bool playerFrontOfMe(std::vector<Player *> players);
    bool playerBelowMe(std::vector<Player *> players);
    bool playerAboveMe(std::vector<Player *> players);
    
    //recupère le sprite courant
    std::string getStateString();
    
    //dessine toi
    void drawHimself(SDL_Surface * sprite, SDL_Surface * dest);
private:
    
    bool getGridValue(int cell);
    int getGidPosition(int offset);
    bool searchPlatformBelow(int cell);
    
};
#endif

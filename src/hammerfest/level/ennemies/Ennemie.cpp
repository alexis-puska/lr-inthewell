#include "Ennemie.h"

Ennemie::Ennemie(int id, int x, int y, int type) :
Position((x * 20) +10 , (y * 20) + 20), Drawable(), HitBox(), IdElement(id) {
    initHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight, ennemieHitboxWidth, ennemieHitboxHeight);
}

Ennemie::~Ennemie() {
    
}

void Ennemie::doSomething(SDL_Surface * dest) {
}


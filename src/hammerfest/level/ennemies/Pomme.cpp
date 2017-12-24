#include "Pomme.h"

Pomme::Pomme(int id, int x, int y, Level * level) :
Ennemie(id, x, y, pomme, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Pomme::~Pomme() {
}

void Pomme::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    if(touchWall() || isOnEdge()){
        if(direction == left){
            direction = right;
        }else{
            direction = left;
        }
    }
    move();
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

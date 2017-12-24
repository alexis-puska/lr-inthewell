#include "Abricot.h"

Abricot::Abricot(int id, int x, int y, Level *level) :
Ennemie(id, x, y, abricot, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Abricot::~Abricot() {
}

void Abricot::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
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

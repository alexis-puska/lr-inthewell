#include "Orange.h"

Orange::Orange(int id, int x, int y, Level * level) :
Ennemie(id, x, y, orange, level) {
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Orange::~Orange() {
}

void Orange::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
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
    //std::cout << "id : "<<id<<" direction : " <<(direction == left ?"left":"right ")<< getX()<<"\n";
}

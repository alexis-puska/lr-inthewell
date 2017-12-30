#include "Pasteque.h"

Pasteque::Pasteque(int id, int x, int y, Level *level) :
Ennemie(id, x, y, pasteque, level) {
    toRight = true;
    toBottom = true;
    lastInvX = 3;
    lastInvY = 3;
}

Pasteque::~Pasteque() {
}

void Pasteque::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
    SDL_Surface * sprite = NULL;
    if (animIdx >= animIdxMax) {
        animIdx = 0;
    }
    switch(state){
        case walk:
        case angry:
            iMove();
            break;
        case knock_out:
            break;
        case frozed:
            break;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Pasteque::iMove(){
    bool bounceWall = false;
    bool p1 = getGridValue(getGridPosition(getX() - 9, getY()));
    bool p2 = getGridValue(getGridPosition(getX() + 9, getY()));
    bool p3 = getGridValue(getGridPosition(getX() - 9, getY() - 25));
    bool p4 = getGridValue(getGridPosition(getX() + 9, getY() - 25));
    bool p5 = getGridValue(getGridPosition(getX() - 12, getY() - 3));
    bool p6 = getGridValue(getGridPosition(getX() - 12, getY() - 22));
    bool p7 = getGridValue(getGridPosition(getX() + 12, getY() - 3));
    bool p8 = getGridValue(getGridPosition(getX() + 12, getY() - 22));
    if(getX() <= 12 || getX() > (388)){
        inverseDirectionX();
        bounceWall = true;
    }
    if(getY() <= 25 || getY() >500){
        inverseDirectionY();
        bounceWall = true;
    }
    if(!bounceWall){
        if(p1 || p2 || p3 || p4){
            inverseDirectionY();
        }
        if(p5 || p6 || p7 || p8){
            inverseDirectionX();
        }
    }
    movePasteque();
}

void Pasteque::inverseDirectionX(){
    lastInvX = 0;
    if(toRight){
        toRight = false;
    }else{
        toRight = true;
    }
}

void Pasteque::inverseDirectionY(){
    lastInvY = 0;
    if(toBottom){
        setY(getY() - getY()%20);
        toBottom = false;
    }else{
        toBottom = true;
    }
}

int Pasteque::getGridPosition(int posX, int posY) {
    int column = (int)floor(posX / 20);
    int line = (int)floor(posY / 20);
    return (line * 20) + column;
}

void Pasteque::movePasteque(){
    if(toRight){
        setX(getX()+(isAngry ? 6 : 4));
    }else{
        setX(getX()-(isAngry ? 6 : 4));
    }
    if(toBottom){
        setY(getY()+(isAngry ? 6 : 4));
    }else{
        setY(getY()-(isAngry ? 6 : 4));
    }
}
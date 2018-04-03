#include "Orange.h"

Orange::Orange(int id, int x, int y, Level *level) : Ennemie(id, x, y, orange, level)
{
    animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

Orange::~Orange()
{
}

void Orange::doSomething(SDL_Surface *dest, std::vector<Player *> players)
{
    SDL_Surface *sprite = NULL;
    if (animIdx >= animIdxMax)
    {
        animIdx = 0;
    }
    switch (state)
    {
    case walk:
    case angry:
        iMove();
        break;
    case jump:
        ennemieJump();
        break;
    }
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawHimself(sprite, dest);
}

void Orange::iMove()
{
    switch (whatITouch())
    {
    case nothing:
        move();
        break;
    case edgeCanJump:
    case edge:
        if (plateformFrontMe())
        {
            changeState(jump);
            initJump(direction, 0);
        }
        else
        {
            changeDirection();
            move();
        }
        break;
    case wall:
    case bottomHighStairs:
    case bottomStairs:
    case topStaires:
        changeDirection();
        move();
        break;
    }
}
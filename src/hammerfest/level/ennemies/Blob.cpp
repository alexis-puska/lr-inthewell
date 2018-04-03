#include "Blob.h"

#define radius 4

Blob::Blob(int id, int x, int y, Level *level) : Ennemie(id, x, y, blob, level)
{
    //need specific initialisation to fix the blob on the correct wall
    onTop = true;
    onLeft = true;
    direction = left;
}

Blob::~Blob()
{
}

void Blob::doSomething(SDL_Surface *dest, std::vector<Player *> players)
{
    SDL_Surface *sprite = NULL;
    if (animIdx >= animIdxMax)
    {
        animIdx = 0;
    }
    iMove();
    sprite = Sprite::Instance().getAnimation(getStateString(), animIdx);
    drawBlob(sprite, dest);
}

void Blob::iMove()
{
    bool plu = getGridValue(getGridPosition(getX() - radius, getY() - 1));
    bool pld = getGridValue(getGridPosition(getX() - radius, getY() + 1));
    bool pul = getGridValue(getGridPosition(getX() - 1, getY() - radius));
    bool pur = getGridValue(getGridPosition(getX() + 1, getY() - radius));
    bool pru = getGridValue(getGridPosition(getX() + radius, getY() - 1));
    bool prd = getGridValue(getGridPosition(getX() + radius, getY() + 1));
    bool pdl = getGridValue(getGridPosition(getX() - 1, getY() + radius));
    bool pdr = getGridValue(getGridPosition(getX() + 1, getY() + radius));
    if (getX() <= 0)
    {
        setX(0);
        plu = true;
        pld = true;
        pdl = true;
        pul = true;
    }
    if (getX() >= 400)
    {
        setX(400);
        pru = true;
        prd = true;
        pur = true;
        pdr = true;
    }
    if (getY() <= 0)
    {
        setY(0);
        pul = true;
        pur = true;
        pru = true;
        plu = true;
    }
    if (getY() >= 500)
    {
        setY(500);
        pdl = true;
        pdr = true;
        pld = true;
        prd = true;
    }

    switch (direction)
    {
    case left:
        if (onTop)
        {
            if (plu)
            {
                direction = up;
                onLeft = true;
                adjustPosition();
                break;
            }
            //if(!pld){
            if (!pdl)
            {
                direction = down;
                onLeft = false;
                adjustPosition();
                break;
            }
        }
        else
        {
            //if(!plu){
            if (!pul)
            {
                direction = up;
                onLeft = false;
                adjustPosition();
                break;
            }
            if (pld)
            {
                direction = down;
                onLeft = true;
                adjustPosition();
                break;
            }
        }
        break;
    case up:
        if (onLeft)
        {
            //if(!pul){
            if (!plu)
            {
                direction = left;
                onTop = true;
                adjustPosition();
                break;
            }
            if (pur)
            {
                direction = right;
                onTop = false;
                adjustPosition();
                break;
            }
        }
        else
        {
            if (pul)
            {
                direction = left;
                onTop = false;
                adjustPosition();
                break;
            }
            if (!pru)
            {
                //if(!pur){
                direction = right;
                onTop = true;
                adjustPosition();
                break;
            }
        }
        break;
    case right:
        if (onTop)
        {
            if (pru)
            {
                direction = up;
                onLeft = false;
                adjustPosition();
                break;
            }
            //if(!prd){
            if (!pdr)
            {
                direction = down;
                onLeft = true;
                adjustPosition();
                break;
            }
        }
        else
        {
            //if(!pru){
            if (!pur)
            {
                direction = up;
                onLeft = true;
                adjustPosition();
                break;
            }
            if (prd)
            {
                direction = down;
                onLeft = false;
                adjustPosition();
                break;
            }
        }
        break;
    case down:
        if (onLeft)
        {
            //if(!pdl){
            if (!pld)
            {
                direction = left;
                onTop = false;
                adjustPosition();
                break;
            }
            if (pdr)
            {
                direction = right;
                onTop = true;
                adjustPosition();
                break;
            }
        }
        else
        {
            if (pdl)
            {
                direction = left;
                onTop = true;
                adjustPosition();
                break;
            }
            //if(!pdr){
            if (!prd)
            {
                direction = right;
                onTop = false;
                adjustPosition();
                break;
            }
        }
        break;
    }

    std::cout << "\n\n";

    switch (direction)
    {
    case left:
        setX(getX() - (isAngry ? 3 : 2));
        break;
    case up:
        setY(getY() - (isAngry ? 3 : 2));
        break;
    case right:
        setX(getX() + (isAngry ? 3 : 2));
        break;
    case down:
        setY(getY() + (isAngry ? 3 : 2));
        break;
    }
}

void Blob::adjustPosition()
{
    if (getX() % 20 != 0)
    {
        if (getX() % 20 > 10)
        {
            setX(getX() - (getX() % 20) + 20);
        }
        else
        {
            setX(getX() - (getX() % 20));
        }
    }
    if (getY() % 20 != 0)
    {
        if (getY() % 20 > 10)
        {
            setY(getY() - (getY() % 20) + 20);
        }
        else
        {
            setY(getY() - (getY() % 20));
        }
    }
}

void Blob::drawBlob(SDL_Surface *sprite, SDL_Surface *dest)
{
    switch (direction)
    {
    case left:
        if (onTop)
        {
            copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w / 2)) + leftPadding, y - (sprite->h));
            break;
        }
        else
        {
            copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w / 2)) + leftPadding, y);
            break;
        }

    case up:
        if (onLeft)
        {
            copySurfaceToBackRenderer(sprite, dest, (x) + leftPadding, y - (sprite->h / 2));
            break;
        }
        else
        {
            copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w)) + leftPadding, y - (sprite->h / 2));
            break;
        }
    case right:
        if (onTop)
        {
            copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w / 2)) + leftPadding, y - (sprite->h));
            break;
        }
        else
        {
            copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w / 2)) + leftPadding, y);
            break;
        }
    case down:
        if (onLeft)
        {
            copySurfaceToBackRenderer(sprite, dest, (x) + leftPadding, y - (sprite->h / 2));
            break;
        }
        else
        {
            copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w)) + leftPadding, y - (sprite->h / 2));
            break;
        }
    }
    updateHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight);
    animIdx++;
}

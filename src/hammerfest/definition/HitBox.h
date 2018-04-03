#ifdef IS_OSX
#include <SDL2_image/SDL_image.h>
#elif WIN32
#include <SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif
#include <iostream>

#ifndef __MYCLASS_HITBOX
#define __MYCLASS_HITBOX

class HitBox
{
  public:
    HitBox();
    void initHitBox(int x, int y, int width, int height);
    virtual ~HitBox();
    void updateHitBox(int x, int y);
    bool hit(SDL_Rect other);
    bool hitMeByBottonOrTopSide(SDL_Rect other);
    int getIntersect(SDL_Rect other, bool horizontal);
    SDL_Rect getRect();

  private:
    SDL_Rect rect;
    int hitBoxWidth;
    int hitBoxHeight;
};

#endif

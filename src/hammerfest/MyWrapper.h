#ifndef __MYWRAPPER_H
#define __MYWRAPPER_H
#include <SDL2/SDL.h>
#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef struct Hammerfest Hammerfest;

Hammerfest* newHammerfest(SDL_Surface * vout_buf);
void hammerfest_tick(Hammerfest *v, unsigned short in_keystate[16]);

//SDL_Surface * hammerfest_getScreen(Hammerfest* v);
void hammerfest_swapBuffer(Hammerfest* v);
void deleteHammerfest(Hammerfest* v);

#ifdef __cplusplus
}
#endif
#endif

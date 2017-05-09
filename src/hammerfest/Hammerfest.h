#include <SDL2/SDL.h>
#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif

#include <stdio.h>


#ifndef __MYCLASS_HAMMERFEST
#define __MYCLASS_HAMMERFEST
class Hammerfest {

	public:
		Hammerfest(SDL_Surface * vout_bufLibretro);
		~Hammerfest();
		void tick(unsigned short in_keystateLibretro[16]);
	private:

		void copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y);

		//buffer for draw
		SDL_Surface *screenBuffer;
		SDL_Surface * vout_buf;

};
#endif

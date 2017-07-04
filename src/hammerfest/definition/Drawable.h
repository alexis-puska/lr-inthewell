#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>
#else
#include <SDL2_image/SDL_image.h>
#include <SDL2_gfx/SDL2_rotozoom.h>
#endif

#include "../utils/Sprite.h"

#ifndef __MYCLASS_DRAWABLE
#define __MYCLASS_DRAWABLE

class Drawable{
	public:
		Drawable();
		virtual ~Drawable();
		virtual void drawHimself(SDL_Surface * dest);
	protected:
		int width;
		int height;
		void copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y, int lengthX, int lengthY);
		void copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y);
		void copySurfaceToBackRendererWithStartOffset(SDL_Surface * src, SDL_Surface * dest, int x, int y, int lengthX, int lengthY, int offsetX, int offsetY);
	private:
};
#endif

#ifndef __MYCLASS_ITEM
#define __MYCLASS_ITEM

#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif

#include <string.h>

#define sizeX 32
#define sizeY 32

class Item {
	public:
		Item();
		~Item();
		Item(SDL_Surface * items, int id, const char * name, int rarity, int value, int unlock);
		int getId();
		char* getName();
		int getRarity();
		int getUnlock();
		int getValue();
		SDL_Surface * getSprite();
		void printName();
	private:
		int id;
		char name[50];
		int value;
		int rarity;
		int unlock;
		SDL_Surface * sprite;
};
#endif

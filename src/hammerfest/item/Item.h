#ifndef __MYCLASS_ITEM
#define __MYCLASS_ITEM

#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif

#include <string>

#define sizeX 32
#define sizeY 32

class Item {
	public:
		Item();
		~Item();
		Item(SDL_Surface * items, int id, std::string name, int rarity, int value, int unlock);
		int getId();
		std::string getName();
		int getRarity();
		int getUnlock();
		int getValue();
		SDL_Surface * getSprite();
		void printName();
	private:
		int id;
		std::string name;
		int value;
		int rarity;
		int unlock;
		SDL_Surface * sprite;
};
#endif

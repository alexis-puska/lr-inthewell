#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#else
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <map>

#ifndef __MYCLASS_SPRITE
#define __MYCLASS_SPRITE

#include "json/json.h"

enum textColor {
	red = 0, blue = 1, green = 2, gold = 3
};

class Sprite {

	public:
		static Sprite& Instance();
		Sprite();
		~Sprite();
		SDL_Surface * getAnimation(std::string name, int index);
		SDL_Color getSDL_Color(int color);
		void drawText(SDL_Surface* surfaceToDraw, int x, int y, const char* text, int color, bool alignCenter);

	private:
		Sprite& operator=(const Sprite&);
		Sprite(const Sprite&);
		static Sprite m_instance;

		/***********************
		 * VARIABLES
		 ***********************/
		SDL_Surface * surfaceToParse;
		std::map<std::string, SDL_Surface **> sprites;

		/***********************
		 * FUNCTIONS
		 ***********************/
		void parseJsonFile();
		void releaseSurfaceToParse();
		void loadSurfaceToSprite(std::string name);

		/*
		 *	FONT
		 */
		TTF_Font* font;
};
#endif

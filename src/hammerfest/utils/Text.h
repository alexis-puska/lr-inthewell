#ifdef IS_OSX
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif WIN32
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#ifndef __MYCLASS_TEXT
#define __MYCLASS_TEXT

#include "json/json.h"
#include "GameConfig.h"

enum textColor
{
	red = 0,
	blue = 1,
	green = 2,
	gold = 3,
	white = 4
};

class Text
{

  public:
	static Text &Instance();
	Text();
	~Text();
	SDL_Color getSDL_Color(int color);
	void drawText(SDL_Surface *surfaceToDraw, std::string fontName, int x, int y, const char *text, int color, bool alignCenter);
	void drawTextTranslated(SDL_Surface *surfaceToDraw, std::string fontName, int x, int y, std::string key, int color, bool alignCenter);

	void addTraduction(std::string lang, std::string key, std::string value);
	std::string getTraduction(std::string key);
	std::string getItemsTranslationKey(int id);
	std::string getQuestTitle(int id);
	std::string getQuestDescription(int id);

  private:
	Text &operator=(const Text &);
	Text(const Text &);

	void parseJsonFile();

	/***********************
	*        FONT
	***********************/
	std::map<std::string, TTF_Font *> fonts;
	std::map<std::string, std::map<std::string, std::string> > texts;
};
#endif

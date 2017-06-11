#include "Text.h"

#include "resources/font_courier_new.h"
#include "resources/font_franklin_gothic_heavy_all.h"
#include "resources/font_impact.h"
#include "resources/font_satans.h"
#include "resources/font_verdana_10pt.h"
#include "resources/font_verdana.h"
#include "resources/font_verdana_bold.h"

const static SDL_Color whiteColor = { 255, 255, 255 };
const static SDL_Color greenColor = { 0, 255, 0 };
const static SDL_Color redColor = { 255, 0, 0 };
const static SDL_Color blueColor = { 0, 140, 255 };
const static SDL_Color goldColor = { 255, 255, 0 };

Text Text::m_instance = Text();

Text::Text() {
	TTF_Init();
	fprintf(stderr, "Init Text system\n");
	fonts["satan24"] =  TTF_OpenFontRW(SDL_RWFromMem(font_satans_ttf, font_satans_ttf_len),1, 24);
	fonts["gothic24"] =  TTF_OpenFontRW(SDL_RWFromMem(font_franklin_gothic_heavy_all_ttf, font_franklin_gothic_heavy_all_ttf_len),1, 24);
	fonts["impact24"] =  TTF_OpenFontRW(SDL_RWFromMem(font_impact_ttf, font_impact_ttf_len),1, 24);
	fonts["verdana24"] =  TTF_OpenFontRW(SDL_RWFromMem(font_verdana_ttf, font_verdana_ttf_len),1, 24);
	fonts["verdanaBold20"] =  TTF_OpenFontRW(SDL_RWFromMem(font_verdana_bold_ttf, font_verdana_bold_ttf_len),1, 20);
	fonts["courrier24"] =  TTF_OpenFontRW(SDL_RWFromMem(font_courier_new_ttf, font_courier_new_ttf_len),1, 24);
	fonts["verdana10pt10"] = TTF_OpenFontRW(SDL_RWFromMem(font_verdana_10pt_ttf, font_verdana_10pt_ttf_len),1, 10);
}

Text::~Text() {
	fprintf(stderr, "close text system\n");
	TTF_Quit();
}

Text& Text::Instance() {
	return m_instance;
}

/********************************************
 *
 *		DRAW TEXT FUNCTION
 *
 ********************************************/
void Text::drawText(SDL_Surface* surfaceToDraw, std::string fontName, int x, int y, const char* text, int color, bool alignCenter) {
	SDL_Color colorSelected = getSDL_Color(color);
	SDL_Surface *text_surface = text_surface = TTF_RenderText_Solid(fonts[fontName], text, colorSelected);
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = text_surface->w;
	srcRect.h = text_surface->h;
	SDL_Rect dstRect;
	if (alignCenter) {
		dstRect.x = x - (text_surface->w / 2);
	} else {
		dstRect.x = x;
	}
	dstRect.y = y;
	dstRect.w = text_surface->w;
	dstRect.h = text_surface->h;
	SDL_BlitSurface(text_surface, &srcRect, surfaceToDraw, &dstRect);
	SDL_FreeSurface(text_surface);
}

SDL_Color Text::getSDL_Color(int color) {
	switch (color) {
		case white:
			return whiteColor;
			break;
		case red:
			return redColor;
			break;
		case blue:
			return blueColor;
			break;
		case green:
			return greenColor;
			break;
		case gold:
			return goldColor;
			break;
	}
	return greenColor;
}

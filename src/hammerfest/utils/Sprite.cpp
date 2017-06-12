#include "Sprite.h"

#include "resources/sprite_animation.h"
#include "resources/sprite_arrow.h"
#include "resources/sprite_background_effect.h"
#include "resources/sprite_big_crystal.h"
#include "resources/sprite_bombe.h"
#include "resources/sprite_ennemies.h"
#include "resources/sprite_level.h"
#include "resources/sprite_light.h"
#include "resources/sprite_map.h"
#include "resources/sprite_objets.h"
#include "resources/sprite_player.h"
#include "resources/image_menu.h"
#include "resources/json_image_parser.h"

Sprite Sprite::m_instance = Sprite();

Sprite::Sprite() {
	IMG_Init (IMG_INIT_PNG);
	fprintf(stderr, "Init sprite system\n");
	parseJsonFile();
}

Sprite::~Sprite() {
	fprintf(stderr, "close sprite system\n");
	IMG_Quit();
}

Sprite& Sprite::Instance() {
	return m_instance;
}

void Sprite::parseJsonFile() {
	Json::Reader reader;
	Json::Value root;
	Json::Value element;
	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0xff000000;

	std::string currentFileParse;
	std::string jsonString(json_image_parser_json, json_image_parser_json + sizeof json_image_parser_json / sizeof json_image_parser_json[0]);
	reader.parse(jsonString, root);
	int idx = 0;

	for (unsigned int i = 0; i < root.size(); i++) {
		if (currentFileParse.empty()) {
			currentFileParse = root[i]["file"].asString();
			loadSurfaceToSprite(root[i]["file"].asString());
			//fprintf(stderr, "load surface : %s\n", currentFileParse.c_str());
		} else if (currentFileParse.compare(root[i]["file"].asString()) != 0) {
			//fprintf(stderr, "release surface : %s\n", currentFileParse.c_str());
			currentFileParse = root[i]["file"].asString();
			releaseSurfaceToParse();
			//fprintf(stderr, "load surface : %s\n", currentFileParse.c_str());
			loadSurfaceToSprite(root[i]["file"].asString());
		}
		for (unsigned int j = 0; j < root[i]["area"].size(); j++) {
			element = root[i]["area"];
			int x = element[j]["x"].asUInt();
			int y = element[j]["y"].asUInt();
			int nx = element[j]["nx"].asUInt();
			int ny = element[j]["ny"].asUInt();
			int n = element[j]["n"].asUInt();
			int sx = element[j]["sx"].asUInt();
			int sy = element[j]["sy"].asUInt();
			bool r = element[j]["r"].asBool();
			std::string anim = element[j]["animation"].asString();
			std::stringstream ss;
			ss << anim << "_flip";
			std::string anim_flip = ss.str();
			idx = 0;
			SDL_Rect srcTextureRect;
			SDL_Rect destTextureRect;
			destTextureRect.x = 0;
			destTextureRect.y = 0;
			destTextureRect.w = sx;
			destTextureRect.h = sy;
			sprites[anim] = new SDL_Surface *[n];
			if(r){
				sprites[anim_flip] = new SDL_Surface *[n];
			}
			//fprintf(stderr, "begin parse file : %s, area: %i %i %i %i %i %i %i %s %s \n", currentFileParse.c_str(), x, y, nx, ny, n, sx, sy, r ? "true" : "false", anim.c_str());
			for (int l = 0; l < ny; l++) {
				for (int k = 0; k < nx; k++) {
					srcTextureRect.x = x + (k * sx);
					srcTextureRect.y = y + (l * sy);
					srcTextureRect.w = sx;
					srcTextureRect.h = sy;
					sprites[anim][idx] = SDL_CreateRGBSurface(0, sx, sy, 32, rmask, gmask, bmask, amask);
					SDL_BlitSurface(surfaceToParse, &srcTextureRect, sprites[anim][idx], &destTextureRect);
					if(r){
						sprites[anim_flip][idx] = SDL_CreateRGBSurface(0, sx, sy, 32, rmask, gmask, bmask, amask);
						SDL_BlitSurface(surfaceToParse, &srcTextureRect, sprites[anim_flip][idx], &destTextureRect);
						sprites[anim_flip][idx] = rotozoomSurfaceXY(sprites[anim_flip][idx], 0, -1, 1, 0);
					}
					idx++;
					if (idx >= n) {
						break;
					}
				}
			}
		}
	}
	releaseSurfaceToParse();
}

void Sprite::releaseSurfaceToParse() {
	SDL_FreeSurface(surfaceToParse);
}

void Sprite::loadSurfaceToSprite(std::string name) {
	if (name.compare("sprite_animation") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_animation_png, sprite_animation_png_len));
	} else if (name.compare("sprite_arrow") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_arrow_png, sprite_arrow_png_len));
	} else if (name.compare("sprite_background_effect") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_background_effect_png, sprite_background_effect_png_len));
	} else if (name.compare("sprite_big_crystal") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_big_crystal_png, sprite_big_crystal_png_len));
	} else if (name.compare("sprite_bombe") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_bombe_png, sprite_bombe_png_len));
	} else if (name.compare("sprite_ennemies") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_ennemies_png, sprite_ennemies_png_len));
	} else if (name.compare("sprite_level") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_level_png, sprite_level_png_len));
	} else if (name.compare("sprite_light") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_light_png, sprite_light_png_len));
	} else if (name.compare("sprite_map") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_map_png, sprite_map_png_len));
	} else if (name.compare("sprite_objets") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_objets_png, sprite_objets_png_len));
	} else if (name.compare("sprite_player") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_player_png, sprite_player_png_len));
	} else if (name.compare("image_menu") == 0) {
		surfaceToParse = IMG_LoadPNG_RW(SDL_RWFromMem(image_menu_png, image_menu_png_len));
	}
}

SDL_Surface * Sprite::getAnimation(std::string name, int index) {
	return sprites[name][index];
}

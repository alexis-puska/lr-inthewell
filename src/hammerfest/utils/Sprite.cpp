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

	TTF_Init();
	IMG_Init (IMG_INIT_PNG);
	fprintf(stderr, "Init sprite system\n");

	//fprintf(stderr, "%s", json_image_parser_json);
	Json::Reader reader;
	Json::Value root;
	Json::Value element;
	SDL_Surface * backgroundSurface = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_player_png, sprite_player_png_len));

	std::string jsonString(json_image_parser_json, json_image_parser_json + sizeof json_image_parser_json / sizeof json_image_parser_json[0]);
	reader.parse(jsonString, root);
	int idx = 0;
	for (int i = 0; i < root.size(); i++) {
		for (int j = 0; j < root[i]["area"].size(); j++) {
			element = root[i]["area"];
			//fprintf(stderr, "area : %i %i %i %i %i %i %i %s %s\n", element[j]["x"].asUInt(), element[j]["y"].asUInt(), element[j]["nx"].asUInt(), element[j]["ny"].asUInt(),
			//		element[j]["n"].asUInt(), element[j]["sx"].asUInt(), element[j]["sy"].asUInt(), element[j]["r"].asBool() ? "true" : "false", element[j]["animation"].asCString());
			idx = 0;
			for (int y = 0; y < element[j]["ny"].asUInt(); y++) {
				for (int x = 0; x < element[j]["nx"].asUInt(); x++) {

					idx++;
				}
			}
		}
	}
	fprintf(stderr, "\n\n\n\nEnd init sprite system\n");
}

Sprite::~Sprite() {
	fprintf(stderr, "close sprite system\n");
	fprintf(stderr, "close font text system\n");
	//TTF_CloseFont(font);‹‹
	IMG_Quit();
	TTF_Quit();
}

Sprite& Sprite::Instance() {
	return m_instance;
}


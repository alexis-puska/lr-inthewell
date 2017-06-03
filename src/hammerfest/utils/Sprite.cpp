#include "Sprite.h"

//sprite
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

//image
#include "resources/image_menu.h"

//json descriptor
#include "resources/json_image_parser.h"

Sprite Sprite::m_instance = Sprite();

Sprite::Sprite() {

	TTF_Init();
	IMG_Init (IMG_INIT_PNG);
	fprintf(stderr, "Init sprite system\n");

	fprintf(stderr, "%s", json_image_parser_json);

	Json::Reader reader;
	Json::Value root;

	SDL_Surface * backgroundSurface = IMG_LoadPNG_RW(SDL_RWFromMem(sprite_player_png, sprite_player_png_len));

	std::string jsonString(json_image_parser_json, json_image_parser_json + sizeof json_image_parser_json / sizeof json_image_parser_json[0]);
	reader.parse(jsonString, root);
	for (int i = 0; i < root.size(); i++) {
		fprintf(stderr, "test json : %i %i %s\n", root.size(), i, root[i]["file"].asCString());
		fprintf(stderr, "nb area : %i\n", root[i]["area"].size());
		for (int j = 0; j < root[i]["area"].size(); j++) {
		fprintf(stderr, "area : %i %i %i %i %i %i %i %s %s\n", root[i]["area"][j]["x"].asUInt(),
				root[i]["area"][j]["y"].asUInt(),
				root[i]["area"][j]["nx"].asUInt(),
				root[i]["area"][j]["ny"].asUInt(),
				root[i]["area"][j]["n"].asUInt(),
				root[i]["area"][j]["sx"].asUInt(),
				root[i]["area"][j]["sy"].asUInt(),
				root[i]["area"][j]["r"].asBool() ? "true" : "false",
				root[i]["area"][j]["animation"].asCString()
		);
	}
}

fprintf(stderr, "\n\n\n\nEnd init sprite system\n");

}

Sprite::~Sprite() {
fprintf(stderr, "close sprite system\n");

fprintf(stderr, "close font text system\n");
//TTF_CloseFont(font);
IMG_Quit();
TTF_Quit();
}

Sprite& Sprite::Instance() {
return m_instance;
}


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

#include "json/json.h"

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



#ifndef __MYCLASS_SPRITE
#define __MYCLASS_SPRITE

class Sprite {

	public:
		static Sprite& Instance();
		Sprite();
		~Sprite();
	private:
		Sprite& operator=(const Sprite&);
		Sprite(const Sprite&);
		static Sprite m_instance;
};
#endif

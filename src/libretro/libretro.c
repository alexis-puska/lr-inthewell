/*
 * (C) alexis-puska, 2016
 *
 * This work is licensed under the terms of the GNU GPLv2 or later.
 * See the COPYING file in the top-level directory.
 */

#define _GNU_SOURCE 1
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "libretro.h"
#include "../hammerfest/MyWrapper.h"
#include <SDL2/SDL.h>
#include <unistd.h>
#ifndef IS_OSX
#include <SDL2/SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#endif

#define VOUT_MAX_WIDTH 420
#define VOUT_MAX_HEIGHT 520
#define VOUT_WIDTH 420
#define VOUT_HEIGHT 520

enum {
	DKEY_SELECT = 0, DKEY_L3, DKEY_R3, DKEY_START, DKEY_UP, DKEY_RIGHT, DKEY_DOWN, DKEY_LEFT, DKEY_L2, DKEY_R2, DKEY_L1, DKEY_R1, DKEY_TRIANGLE, DKEY_CIRCLE, DKEY_CROSS, DKEY_SQUARE,
};

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;
static struct retro_rumble_interface rumble;
static bool support_no_game = true;

static struct Hammerfest* hammerfest;
static unsigned short in_keystate[2];
static SDL_Surface * vout_buf;

char * savePath;
char saveFilePath[255];
FILE* fichier;
bool writeInFile = false;

static const unsigned short retro_psx_map[] = { [RETRO_DEVICE_ID_JOYPAD_B] = 1 << DKEY_CROSS, [RETRO_DEVICE_ID_JOYPAD_Y] = 1 << DKEY_SQUARE, [RETRO_DEVICE_ID_JOYPAD_SELECT] = 1 << DKEY_SELECT,
		[RETRO_DEVICE_ID_JOYPAD_START] = 1 << DKEY_START, [RETRO_DEVICE_ID_JOYPAD_UP] = 1 << DKEY_UP, [RETRO_DEVICE_ID_JOYPAD_DOWN] = 1 << DKEY_DOWN,
		[RETRO_DEVICE_ID_JOYPAD_LEFT] = 1 << DKEY_LEFT, [RETRO_DEVICE_ID_JOYPAD_RIGHT] = 1 << DKEY_RIGHT, [RETRO_DEVICE_ID_JOYPAD_A] = 1 << DKEY_CIRCLE, [RETRO_DEVICE_ID_JOYPAD_X] = 1
				<< DKEY_TRIANGLE, [RETRO_DEVICE_ID_JOYPAD_L] = 1 << DKEY_L1, [RETRO_DEVICE_ID_JOYPAD_R] = 1 << DKEY_R1, [RETRO_DEVICE_ID_JOYPAD_L2] = 1 << DKEY_L2, [RETRO_DEVICE_ID_JOYPAD_R2
				] = 1 << DKEY_R2, };
#define RETRO_PSX_MAP_LEN (sizeof(retro_psx_map) / sizeof(retro_psx_map[0]))

/* libretro */
void retro_set_environment(retro_environment_t cb) {
	environ_cb = cb;
}

void retro_set_audio_sample(retro_audio_sample_t cb) {
	audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {
	audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb) {
	input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb) {
	input_state_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb) {
	video_cb = cb;
}

unsigned retro_api_version(void) {
	return RETRO_API_VERSION;
}

void retro_set_controller_port_device(unsigned port, unsigned device) {
}

void retro_get_system_info(struct retro_system_info *info) {
	memset(info, 0, sizeof(*info));
	info->library_name = "lr_hammerfest_libretro";
	info->library_version = "r1";
	info->valid_extensions = NULL;
	info->need_fullpath = false;
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
	memset(info, 0, sizeof(*info));
	info->timing.fps = 60;
	info->timing.sample_rate = 44100;
	info->geometry.base_width = VOUT_WIDTH;
	info->geometry.base_height = VOUT_HEIGHT;
	info->geometry.max_width = VOUT_MAX_WIDTH;
	info->geometry.max_height = VOUT_MAX_HEIGHT;
}

/* savestates */
size_t retro_serialize_size(void) {
	return 0x440000;
}

bool retro_serialize(void *data, size_t size) {
	return false;
}

bool retro_unserialize(const void *data, size_t size) {
	return false;
}

/* cheats */
void retro_cheat_reset(void) {
}

void retro_cheat_set(unsigned index, bool enabled, const char *code) {
}

bool retro_load_game(const struct retro_game_info *info) {
	struct retro_input_descriptor desc[] = { { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left" }, { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up" }, { 0,
	RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down" }, { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" }, { 0, RETRO_DEVICE_JOYPAD, 0,
	RETRO_DEVICE_ID_JOYPAD_B, "Cross" }, { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Circle" }, { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Triangle" }, { 0,
	RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Square" }, { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L1" }, { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "L2" }, { 0,
	RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R1" }, { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "R2" }, { 0, RETRO_DEVICE_JOYPAD, 0,
	RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" }, { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },

	{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left" }, { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up" }, { 1, RETRO_DEVICE_JOYPAD, 0,
	RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down" }, { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" }, { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Cross" }, { 1,
	RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Circle" }, { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Triangle" }, { 1, RETRO_DEVICE_JOYPAD, 0,
	RETRO_DEVICE_ID_JOYPAD_Y, "Square" }, { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L1" }, { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "L2" }, { 1,
	RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R1" }, { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "R2" }, { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
			{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },

			{ 0 }, };

	environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);

	enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
	if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
		fprintf(stderr, "XRGB8888 is not supported.\n");
		return false;
	}
	return true;
}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) {
	return false;
}

void retro_unload_game(void) {
}

unsigned retro_get_region(void) {
	return RETRO_REGION_PAL;
}

void *retro_get_memory_data(unsigned id) {
	return NULL;
}

size_t retro_get_memory_size(unsigned id) {
	return 0;
}

void retro_reset(void) {
	deleteHammerfest(hammerfest);
	hammerfest = newHammerfest(vout_buf);
}

void retro_init(void) {
	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0xff000000;
	vout_buf = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(vout_buf, NULL, SDL_MapRGB(vout_buf->format, 255, 204, 0));
	hammerfest = newHammerfest(vout_buf);
	environ_cb(RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE, &rumble);
	unsigned level = 0;
	environ_cb(RETRO_ENVIRONMENT_SET_PERFORMANCE_LEVEL, &level);
	environ_cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &support_no_game);

	if (environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &savePath) &&savePath) {
		if (strcmp(savePath, "") == 0) {
			fprintf(stderr, "Save directory not set in retroarch.cfg so use content directory !\n");
			environ_cb(RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY, &savePath);
		}
		strcpy(saveFilePath, savePath);
		strcat(saveFilePath, "/lr_hammerfest_libretro.srm");
		fprintf(stderr, "save dir : %s\n", saveFilePath);

		if (access(saveFilePath, F_OK) != -1) {
			fprintf(stderr, "saving file found : %s\n", saveFilePath);
			fichier = fopen(saveFilePath, "r+");
		} else {
			fprintf(stderr, "saving file doesn't exist, create one\n");
			fichier = fopen(saveFilePath, "w");
		}
	}
	fprintf(stderr, "Loaded game!\n");
}

void retro_deinit(void) {
	deleteHammerfest(hammerfest);
	SDL_FreeSurface(vout_buf);
	fclose(fichier);
}

void retro_run(void) {
	// reset all keystate, query libretro for keystate
	int i;
	int j;
	for (i = 0; i < 2; i++) {
		in_keystate[i] = 0;
		// query libretro for keystate
		for (j = 0; j < RETRO_PSX_MAP_LEN; j++) {
			if (input_state_cb(i, RETRO_DEVICE_JOYPAD, 0, j)) {
				in_keystate[i] |= retro_psx_map[j];
			}
		}
	}
	hammerfest_tick(hammerfest, in_keystate);
	video_cb(vout_buf->pixels, VOUT_WIDTH, VOUT_HEIGHT, VOUT_WIDTH * 4);

	rewind(fichier);
	//fprintf(fichier,"%x",13211);

	int len = 15;
	unsigned char test[15] = {0x99, 0x98, 0x97, 0x98, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x95};
	if(!writeInFile){
	for(int i = 0;i < 15;i++){
		fprintf(fichier,"%x",test[i]);
	}
	writeInFile = true;
	}
	/*
	 unsigned int read;
	 rewind(fichier);
	 for(int i = 0;i < 15;i++){
	 fscanf(fichier,"%x",&read);
	 fprintf(stderr,"%x",read);
	 }
	 fprintf(stderr,"\n");
	 */
	//char str[80];
	//fscanf(fichier,"%s", str);
	//rewind(fichier);
	//fprintf(stderr, "%s\n", str);
	//fprintf(stderr, "%s", content);
}

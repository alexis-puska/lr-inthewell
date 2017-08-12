#include <iostream>

#include <stdio.h>

#include "hammerfest/Hammerfest.h"

#ifdef IS_OSX
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_gfx/SDL2_rotozoom.h>
#elif WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_rotozoom.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>
#endif

#define RETRO_DEVICE_ID_JOYPAD_B        0
#define RETRO_DEVICE_ID_JOYPAD_Y        1
#define RETRO_DEVICE_ID_JOYPAD_SELECT   2
#define RETRO_DEVICE_ID_JOYPAD_START    3
#define RETRO_DEVICE_ID_JOYPAD_UP       4
#define RETRO_DEVICE_ID_JOYPAD_DOWN     5
#define RETRO_DEVICE_ID_JOYPAD_LEFT     6
#define RETRO_DEVICE_ID_JOYPAD_RIGHT    7
#define RETRO_DEVICE_ID_JOYPAD_A        8
#define RETRO_DEVICE_ID_JOYPAD_X        9
#define RETRO_DEVICE_ID_JOYPAD_L       10
#define RETRO_DEVICE_ID_JOYPAD_R       11
#define RETRO_DEVICE_ID_JOYPAD_L2      12
#define RETRO_DEVICE_ID_JOYPAD_R2      13
#define RETRO_DEVICE_ID_JOYPAD_L3      14
#define RETRO_DEVICE_ID_JOYPAD_R3      15

enum {
	DKEY_SELECT = 0,
	DKEY_L3,
	DKEY_R3,
	DKEY_START,
	DKEY_UP,
	DKEY_RIGHT,
	DKEY_DOWN,
	DKEY_LEFT,
	DKEY_L2,
	DKEY_R2,
	DKEY_L1,
	DKEY_R1,
	DKEY_TRIANGLE,
	DKEY_CIRCLE,
	DKEY_CROSS,
	DKEY_SQUARE,
};

static const unsigned short retro_psx_map[] = { 1 << DKEY_CROSS, 1 << DKEY_SQUARE, 1 << DKEY_SELECT, 1 << DKEY_START, 1 << DKEY_UP, 1 << DKEY_DOWN, 1
		<< DKEY_LEFT, 1 << DKEY_RIGHT, 1 << DKEY_CIRCLE, 1 << DKEY_TRIANGLE, 1 << DKEY_L1, 1 << DKEY_R1, 1 << DKEY_L2, 1 << DKEY_R2, };

const int WIDTH = 420, HEIGHT = 520;

int main(int argc, char *argv[]) {
	SDL_Init (SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("In the well", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	SDL_Surface * test = SDL_GetWindowSurface(window);

	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0xff000000;

	//init all surface
	SDL_Surface * buffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);

	SDL_FillRect(test, NULL, SDL_MapRGB(test->format, 89, 184, 241));
	SDL_UpdateWindowSurface(window);
	// Check that the window was successfully created
	if (NULL == window) {
		// In the case that the window could not be made...
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event windowEvent;

	SDL_Joystick* pJoystick = NULL;
	int numJoystick = SDL_NumJoysticks(); // Compte le nombre de joysticks
	std::cout << "Vous avez " << numJoystick << " joysticks sur cette machine\n";
	if (numJoystick >= 1) {
		// Ouvre le premier joystick présent sur la machine
		pJoystick = SDL_JoystickOpen(0);
		if (pJoystick == NULL) {
			std::cerr << "Erreur pour ouvrir le premier joystick\n";
		}
	}

	unsigned short in_keystate[16];

	bool newSaveFile = false;

	char saveFilePath[255];
    FILE * saveFile;

	strcat(saveFilePath, "InTheWell.srm");

    if (FILE *file = fopen(saveFilePath, "r")) {
        fclose (saveFile);
        fprintf(stderr, "saving file found : %s\n", saveFilePath);
        saveFile = fopen(saveFilePath, "r+");
        newSaveFile = false;
    } else {
        fprintf(stderr, "saving file doesn't exist, create one\n");
        saveFile = fopen(saveFilePath, "w");
        newSaveFile = true;
    }
    
    
	
	fclose (saveFile);

	Hammerfest hammerfest = Hammerfest(buffer, saveFilePath, newSaveFile);

	char cont = 1;

	while (cont != 0) {
		if (SDL_PollEvent(&windowEvent)) {
			if (SDL_QUIT == windowEvent.type) {
				break;
			}
		}

		SDL_PumpEvents(); // On demande à la SDL de mettre à jour les états sur les périphériques
		// Clavier
		{
			in_keystate[0] = 0;
			const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
			if (pKeyStates[SDL_SCANCODE_ESCAPE]) {
				cont = 0;
			}
			if (pKeyStates[SDL_SCANCODE_RETURN]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_START];
			}
			if (pKeyStates[SDL_SCANCODE_SPACE]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_A];
			}
			if (pKeyStates[SDL_SCANCODE_LEFT]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_LEFT];
			}
			if (pKeyStates[SDL_SCANCODE_RIGHT]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_RIGHT];
			}
			if (pKeyStates[SDL_SCANCODE_UP]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_B];
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_UP];
			}
			if (pKeyStates[SDL_SCANCODE_DOWN]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_Y];
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_DOWN];
			}
			if (pKeyStates[SDL_SCANCODE_LSHIFT]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_A];
			}
			if (pKeyStates[SDL_SCANCODE_C] || pKeyStates[SDL_SCANCODE_RSHIFT]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_SELECT];
			}

			if (pKeyStates[SDL_SCANCODE_C] || pKeyStates[SDL_SCANCODE_G]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_L];
			}

			if (pKeyStates[SDL_SCANCODE_C] || pKeyStates[SDL_SCANCODE_H]) {
				in_keystate[0] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_R];
			}

			// On peut vérifier d'autres touches, si on le souhaite

			SDL_Keymod mod = SDL_GetModState();
			if (mod != KMOD_NONE) {
				std::cout << "Vous avez appuyé sur une touche spéciale : " << mod << "\n";
			}
		}
		// Joystick
		{
			int nbJoysticks = SDL_NumJoysticks();
			int i = 0;
			for (i = 0; i < nbJoysticks; i++) {
				SDL_Joystick* pJoy = SDL_JoystickOpen(i);
				SDL_JoystickUpdate();
				if (pJoy) {
					std::cout << "Joystick " << i << "\n";
					std::cout << "nom " << SDL_JoystickNameForIndex(i) << "\n";
					// Boutons
					{
						int nbBoutons = SDL_JoystickNumButtons(pJoy);
						int bouton = 0;
						in_keystate[i] = 0;
						std::cout << "Nombre de boutons : " << nbBoutons << "\n";
						for (bouton = 0; bouton < nbBoutons; bouton++) {
							std::cout << (int) SDL_JoystickGetButton(pJoy, bouton);

							if (SDL_JoystickGetButton(pJoy, bouton) == 1) {

								switch (bouton) {
									case 0:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_Y];
										break;
									case 1:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_B];
										break;
									case 2:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_A];
										break;
									case 3:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_X];
										break;
									case 4:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_L];
										break;
									case 5:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_R];
										break;
									case 6:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_L2];
										break;
									case 7:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_R2];
										break;
									case 8:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_SELECT];
										break;
									case 9:
										in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_START];
										break;
								}
							}
						}
						std::cout << (int) in_keystate[i] << "\n";
					}

					// Chapeaux
					{
						int nbChapeaux = SDL_JoystickNumHats(pJoy);
						int chapeau = 0;
						for (chapeau = 0; chapeau < nbChapeaux; chapeau++) {
							std::cout << "Chapeau " << chapeau << " : " << (int) SDL_JoystickGetHat(pJoy, chapeau) << "\n";
							switch ((int) SDL_JoystickGetHat(pJoy, chapeau)) {
								case 1:
									in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_UP];
									break;
								case 2:
									in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_RIGHT];
									break;
								case 4:
									in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_DOWN];
									break;
								case 8:
									in_keystate[i] |= retro_psx_map[RETRO_DEVICE_ID_JOYPAD_LEFT];
									break;
							}
						}
					}

					SDL_JoystickClose(pJoy);

				} else {
					std::cerr << "Couldn't open Joystick 0\n";
				}
			}

			hammerfest.tick(in_keystate);

			int x;
			int y;
			SDL_GetWindowSize(window, &x, &y);
			int nx = ceil(x / 420);
			int ny = ceil(y / 520);
			int mul;
			if (nx == ny) {
				mul = nx;
			} else if (nx > ny) {
				mul = ny;
			} else if (nx < ny) {
				mul = nx;
			}
			SDL_Rect dstRect;
			dstRect.x = (x - (mul * 420)) / 2;
			dstRect.y = (y - (mul * 520)) / 2;
			dstRect.w = 420 * mul;
			dstRect.h = 520 * mul;
			SDL_Surface * tmp = rotozoomSurfaceXY(buffer, 0, mul, mul, 0);
			SDL_BlitSurface(tmp, NULL, test, &dstRect);
			SDL_FreeSurface(tmp);

			SDL_UpdateWindowSurface(window);

		}
		SDL_Delay(10);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}

#include "MyWrapper.h"
#include "Hammerfest.h"

extern "C" {
Hammerfest *newHammerfest(SDL_Surface *vout_buf, char *saveFilePath, bool newSaveFile)
{
	return new Hammerfest(vout_buf, saveFilePath, newSaveFile);
}

void deleteHammerfest(Hammerfest *v)
{
	delete v;
}

void hammerfest_tick(Hammerfest *v, unsigned short in_keystate[16])
{
	v->tick(in_keystate);
}
}

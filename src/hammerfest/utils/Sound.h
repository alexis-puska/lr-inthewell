#ifdef IS_OSX
#include <SDL2_mixer/SDL_mixer.h>
#elif WIN32
#include <SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif

#include <iostream>

#ifndef __MYCLASS_Sound
#define __MYCLASS_Sound

#define nbChannelSound 19

class Sound {
	public:
		static Sound& Instance();
		Sound();
		~Sound();

		void startMusicBoss();
		void startMusicHurryUp();
		void startMusic();
		void stopMusique();
		void playSoundBlackBombe();
		void playSoundBlueBombe();
		void playSoundChangeType();
		void playSoundCristal();
		void playSoundDead();
		void playSoundGreenBombe();
		void playSoundHurryUp();
		void playSoundIgorFall();
		void playSoundIgorJump();
		void playSoundKickBombe();
		void playSoundKillEnnemis();
		void playSoundLetterEffectObject();
		void playSoundNormalBombe();
		void playSoundNextLevel();
		void playSoundPop();
		void playSoundPutBombe();
		void playSoundTakeObject();
		void playSoundTeleporter();
		void playSoundTuberculoz();

	private:
		Sound& operator=(const Sound&);
		Sound(const Sound&);
		static Sound m_instance;

		//musique
		Mix_Music *musicBoss;
		Mix_Music *musicHurryUp;
		Mix_Music *music;
		//sound menu
		Mix_Chunk *soundBlackBombe;
		Mix_Chunk *soundBlueBombe;
		Mix_Chunk *soundChangeType;
		Mix_Chunk *soundCristal;
		Mix_Chunk *soundDead;
		Mix_Chunk *soundGreenBombe;
		Mix_Chunk *soundHurryUp;
		Mix_Chunk *soundIgorFall;
		Mix_Chunk *soundIgorJump;
		Mix_Chunk *soundKickBombe;
		Mix_Chunk *soundKillEnnemis;
		Mix_Chunk *soundLetterEffectObject;
		Mix_Chunk *soundNormalBombe;
		Mix_Chunk *soundNextLevel;
		Mix_Chunk *soundPop;
		Mix_Chunk *soundPutBombe;
		Mix_Chunk *soundTakeObject;
		Mix_Chunk *soundTeleporter;
		Mix_Chunk *soundTuberculoz;
};
#endif

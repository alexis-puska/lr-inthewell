#include "Sound.h"

//music
#include "resources/music_boss.h"
#include "resources/music_hurry_up.h"
#include "resources/music_music.h"

//sound
#include "resources/sound_black_bombe.h"
#include "resources/sound_blue_bombe.h"
#include "resources/sound_change_type.h"
#include "resources/sound_cristal.h"
#include "resources/sound_dead.h"
#include "resources/sound_green_bombe.h"
#include "resources/sound_hurry_up.h"
#include "resources/sound_igor_fall.h"
#include "resources/sound_igor_jump.h"
#include "resources/sound_kick_bombe.h"
#include "resources/sound_kill_ennemis.h"
#include "resources/sound_letter_effect_object.h"
#include "resources/sound_next_level.h"
#include "resources/sound_normal_bombe.h"
#include "resources/sound_pop.h"
#include "resources/sound_put_bombe.h"
#include "resources/sound_take_object.h"
#include "resources/sound_teleporter.h"
#include "resources/sound_tuberculoz.h"

Sound Sound::m_instance = Sound();

Sound::Sound() {
    std::cout << "Init sound system\n";
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        std::cout << Mix_GetError();
	}

	musicBoss = Mix_LoadMUSType_RW(SDL_RWFromMem(music_boss_mp3, music_boss_mp3_len), MUS_MP3, 0);
	musicHurryUp = Mix_LoadMUSType_RW(SDL_RWFromMem(music_hurry_up_mp3, music_hurry_up_mp3_len), MUS_MP3, 0);
	music = Mix_LoadMUSType_RW(SDL_RWFromMem(music_music_mp3, music_music_mp3_len), MUS_MP3, 0);

	soundBlackBombe = Mix_LoadWAV_RW(SDL_RWFromMem(sound_black_bombe_wav, sound_black_bombe_wav_len), 0);
	soundBlueBombe = Mix_LoadWAV_RW(SDL_RWFromMem(sound_blue_bombe_wav, sound_blue_bombe_wav_len), 0);
	soundChangeType = Mix_LoadWAV_RW(SDL_RWFromMem(sound_change_type_wav, sound_change_type_wav_len), 0);
	soundCristal = Mix_LoadWAV_RW(SDL_RWFromMem(sound_cristal_wav, sound_cristal_wav_len), 0);
	soundDead = Mix_LoadWAV_RW(SDL_RWFromMem(sound_dead_wav, sound_dead_wav_len), 0);
	soundGreenBombe = Mix_LoadWAV_RW(SDL_RWFromMem(sound_green_bombe_wav, sound_green_bombe_wav_len), 0);
	soundHurryUp = Mix_LoadWAV_RW(SDL_RWFromMem(sound_hurry_up_wav, sound_hurry_up_wav_len), 0);
	soundIgorFall = Mix_LoadWAV_RW(SDL_RWFromMem(sound_igor_fall_wav, sound_igor_fall_wav_len), 0);
	soundIgorJump = Mix_LoadWAV_RW(SDL_RWFromMem(sound_igor_jump_wav, sound_igor_jump_wav_len), 0);
	soundKickBombe = Mix_LoadWAV_RW(SDL_RWFromMem(sound_kick_bombe_wav, sound_kick_bombe_wav_len), 0);
	soundKillEnnemis = Mix_LoadWAV_RW(SDL_RWFromMem(sound_kill_ennemis_wav, sound_kill_ennemis_wav_len), 0);
	soundLetterEffectObject = Mix_LoadWAV_RW(SDL_RWFromMem(sound_letter_effect_object_wav, sound_letter_effect_object_wav_len), 0);
	soundNextLevel = Mix_LoadWAV_RW(SDL_RWFromMem(sound_next_level_wav, sound_next_level_wav_len), 0);
	soundNormalBombe = Mix_LoadWAV_RW(SDL_RWFromMem(sound_normal_bombe_wav, sound_normal_bombe_wav_len), 0);
	soundPop = Mix_LoadWAV_RW(SDL_RWFromMem(sound_pop_wav, sound_pop_wav_len), 0);
	soundPutBombe = Mix_LoadWAV_RW(SDL_RWFromMem(sound_put_bombe_wav, sound_put_bombe_wav_len), 0);
	soundTakeObject = Mix_LoadWAV_RW(SDL_RWFromMem(sound_take_object_wav, sound_take_object_wav_len), 0);
	soundTeleporter = Mix_LoadWAV_RW(SDL_RWFromMem(sound_teleporter_wav, sound_teleporter_wav_len), 0);
	soundTuberculoz = Mix_LoadWAV_RW(SDL_RWFromMem(sound_tuberculoz_wav, sound_tuberculoz_wav_len), 0);

	Mix_VolumeMusic (MIX_MAX_VOLUME);
	Mix_AllocateChannels(nbChannelSound);
}

Sound::~Sound() {
	std::cout << "Close sound system\n";
	Mix_CloseAudio();
	Mix_FreeMusic(musicBoss);
	Mix_FreeMusic(musicHurryUp);
	Mix_FreeMusic(music);
	Mix_FreeChunk(soundBlackBombe);
	Mix_FreeChunk(soundBlueBombe);
	Mix_FreeChunk(soundChangeType);
	Mix_FreeChunk(soundCristal);
	Mix_FreeChunk(soundDead);
	Mix_FreeChunk(soundGreenBombe);
	Mix_FreeChunk(soundHurryUp);
	Mix_FreeChunk(soundIgorFall);
	Mix_FreeChunk(soundIgorJump);
	Mix_FreeChunk(soundKickBombe);
	Mix_FreeChunk(soundKillEnnemis);
	Mix_FreeChunk(soundLetterEffectObject);
	Mix_FreeChunk(soundNextLevel);
	Mix_FreeChunk(soundNormalBombe);
	Mix_FreeChunk(soundPop);
	Mix_FreeChunk(soundPutBombe);
	Mix_FreeChunk(soundTakeObject);
	Mix_FreeChunk(soundTeleporter);
	Mix_FreeChunk(soundTuberculoz);
	Mix_CloseAudio();
}

Sound& Sound::Instance() {
	return m_instance;
}

void Sound::startMusicBoss() {
	Mix_VolumeMusic (MIX_MAX_VOLUME);
	Mix_PlayMusic(musicBoss, -1);
}

void Sound::startMusicHurryUp() {
	Mix_VolumeMusic (MIX_MAX_VOLUME);
	Mix_PlayMusic(musicHurryUp, -1);
}

void Sound::startMusic() {
	Mix_VolumeMusic (MIX_MAX_VOLUME);
	Mix_PlayMusic(music, -1);
}

void Sound::stopMusique() {
	Mix_HaltMusic();
}

void Sound::playSoundBlackBombe() {
	Mix_PlayChannel(0, soundBlackBombe, 0);
}

void Sound::playSoundBlueBombe() {
	Mix_PlayChannel(1, soundBlueBombe, 0);
}

void Sound::playSoundChangeType() {
	Mix_PlayChannel(2, soundChangeType, 0);
}

void Sound::playSoundCristal() {
	Mix_PlayChannel(3, soundCristal, 0);
}

void Sound::playSoundDead() {
	Mix_PlayChannel(4, soundDead, 0);
}

void Sound::playSoundGreenBombe() {
	Mix_PlayChannel(5, soundGreenBombe, 0);
}

void Sound::playSoundHurryUp() {
	Mix_PlayChannel(6, soundHurryUp, 0);
}

void Sound::playSoundIgorFall() {
	Mix_PlayChannel(7, soundIgorFall, 0);
}

void Sound::playSoundIgorJump() {
	Mix_PlayChannel(8, soundIgorJump, 0);
}

void Sound::playSoundKickBombe() {
	Mix_PlayChannel(9, soundKickBombe, 0);
}

void Sound::playSoundKillEnnemis() {
	Mix_PlayChannel(10, soundKillEnnemis, 0);
}

void Sound::playSoundLetterEffectObject() {
	Mix_PlayChannel(11, soundLetterEffectObject, 0);
}

void Sound::playSoundNormalBombe() {
	Mix_PlayChannel(12, soundNormalBombe, 0);
}

void Sound::playSoundPop() {
	Mix_PlayChannel(13, soundPop, 0);
}

void Sound::playSoundPutBombe() {
	Mix_PlayChannel(14, soundPutBombe, 0);
}

void Sound::playSoundTakeObject() {
	Mix_PlayChannel(15, soundTakeObject, 0);
}

void Sound::playSoundTeleporter() {
	Mix_PlayChannel(16, soundTeleporter, 0);
}

void Sound::playSoundTuberculoz() {
	Mix_PlayChannel(17, soundTuberculoz, 0);
}

void Sound::playSoundNextLevel() {
	Mix_PlayChannel(12, soundNextLevel, 0);
}

#include "sound.h"

static void loadSounds(void);
static void loadMusic(void);

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music[MSC_MAX];

void initSounds(void) {
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
	memset(music, 0, sizeof(Mix_Music*) * MSC_MAX);
	loadSounds();
	loadMusic();
	Mix_Volume(CH_CROW, (int)(MIX_MAX_VOLUME * .6f));
	Mix_Volume(CH_PIGEON, (int)(MIX_MAX_VOLUME * .6f));
	Mix_Volume(CH_JUMP, (int)(MIX_MAX_VOLUME * .6f));
	Mix_Volume(CH_ASCEND, (int)(MIX_MAX_VOLUME * .9f));
	Mix_Volume(CH_WIN, (int)(MIX_MAX_VOLUME * .8f));
	Mix_Volume(CH_LOSE, (int)(MIX_MAX_VOLUME * .8f));
	Mix_VolumeMusic((int)(MIX_MAX_VOLUME * .7f));
}

static void loadSounds(void) {
	SDL_RWops* rwCrow = SDL_RWFromConstMem(crow, sizeof(crow));
	SDL_RWseek(rwCrow, 0, RW_SEEK_SET);
	sounds[SND_CROW] = Mix_LoadWAV_RW(rwCrow, 1);

	SDL_RWops* rwPigeon = SDL_RWFromConstMem(pigeon, sizeof(pigeon));
	SDL_RWseek(rwPigeon, 0, RW_SEEK_SET);
	sounds[SND_PIGEON] = Mix_LoadWAV_RW(rwPigeon, 1);

	SDL_RWops* rwJump = SDL_RWFromConstMem(jump, sizeof(jump));
	SDL_RWseek(rwJump, 0, RW_SEEK_SET);
	sounds[SND_JUMP] = Mix_LoadWAV_RW(rwJump, 1);

	SDL_RWops* rwAscend = SDL_RWFromConstMem(ascend, sizeof(ascend));
	SDL_RWseek(rwAscend, 0, RW_SEEK_SET);
	sounds[SND_ASCEND] = Mix_LoadWAV_RW(rwAscend, 1);

	SDL_RWops* rwWin = SDL_RWFromConstMem(win, sizeof(win));
	SDL_RWseek(rwWin, 0, RW_SEEK_SET);
	sounds[SND_WIN] = Mix_LoadWAV_RW(rwWin, 1);

	SDL_RWops* rwLose = SDL_RWFromConstMem(lose, sizeof(lose));
	SDL_RWseek(rwLose, 0, RW_SEEK_SET);
	sounds[SND_LOSE] = Mix_LoadWAV_RW(rwLose, 1);

	SDL_RWops* rwRecord = SDL_RWFromConstMem(record, sizeof(record));
	SDL_RWseek(rwRecord, 0, RW_SEEK_SET);
	sounds[SND_RECORD] = Mix_LoadWAV_RW(rwRecord, 1);
}

static void loadMusic(void) {
	SDL_RWops* rwTitle = SDL_RWFromConstMem(title, sizeof(title));
	SDL_RWseek(rwTitle, 0, RW_SEEK_SET);
	music[MSC_TITLE] = Mix_LoadMUS_RW(rwTitle, 1);

	SDL_RWops* rwStroll = SDL_RWFromConstMem(stroll, sizeof(stroll));
	SDL_RWseek(rwStroll, 0, RW_SEEK_SET);
	music[MSC_STROLL] = Mix_LoadMUS_RW(rwStroll, 1);

	SDL_RWops* rwSprint = SDL_RWFromConstMem(sprint, sizeof(sprint));
	SDL_RWseek(rwSprint, 0, RW_SEEK_SET);
	music[MSC_SPRINT] = Mix_LoadMUS_RW(rwSprint, 1);
}

void playMusic(int id, int fadeIn) {
	Mix_FadeInMusic(music[id], -1, fadeIn);
}

void stopMusic(int fadeOut) {
	Mix_FadeOutMusic(fadeOut);
}

void playSound(int id, int channel) {
	Mix_PlayChannel(channel, sounds[id], 0);
}

void stopSound(int channel, int fadeOut) {
	Mix_FadeOutChannel(channel, fadeOut);
}

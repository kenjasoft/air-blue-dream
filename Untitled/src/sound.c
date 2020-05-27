#include "sound.h"

static void loadSounds(void);
static void loadMusic(void);

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* titleMusic;
static Mix_Music* strollMusic;
static Mix_Music* sprintMusic;

void initSounds(void) {
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
	titleMusic = NULL;
	strollMusic = NULL;
	sprintMusic = NULL;
	loadSounds();
	loadMusic();
}

static void loadSounds(void) {
	//sounds[SND_JUMP] = Mix_LoadWAV("snd\\jump.ogg");
}

static void loadMusic(void) {
	titleMusic = Mix_LoadMUS("ogg\\title.ogg");
	strollMusic = Mix_LoadMUS("ogg\\stroll.ogg");
	sprintMusic = Mix_LoadMUS("ogg\\sprint.ogg");
}

void playMusic(int id, int fadeIn) {
	switch (id) {
	case MSC_TITLE:
		Mix_FadeInMusic(titleMusic, -1, fadeIn);
		break;
	case MSC_STROLL:
		Mix_FadeInMusic(strollMusic, -1, fadeIn);
		break;
	case MSC_SPRINT:
		Mix_FadeInMusic(sprintMusic, -1, fadeIn);
		break;
	default:
		break;
	}
}

void stopMusic(int fadeOut) {
	Mix_FadeOutMusic(fadeOut);
}

void playSound(int id, int channel) {
	Mix_PlayChannel(channel, sounds[id], 0);
}

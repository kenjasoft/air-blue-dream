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
	Mix_Volume(CH_CROW, (int)(MIX_MAX_VOLUME * .75f));
	Mix_Volume(CH_PIGEON, (int)(MIX_MAX_VOLUME * .75f));
	Mix_Volume(CH_JUMP, (int)(MIX_MAX_VOLUME * .75f));
	Mix_VolumeMusic((int)(MIX_MAX_VOLUME * .75f));
}

static void loadSounds(void) {
	sounds[SND_CROW] = Mix_LoadWAV("dat\\crow.ogg");
	sounds[SND_PIGEON] = Mix_LoadWAV("dat\\pigeon.ogg");
	sounds[SND_JUMP] = Mix_LoadWAV("dat\\jump.ogg");
	sounds[SND_ASCEND] = Mix_LoadWAV("dat\\ascend.ogg");
	sounds[SND_WIN] = Mix_LoadWAV("dat\\win.ogg");
	sounds[SND_LOSE] = Mix_LoadWAV("dat\\lose.ogg");
	sounds[SND_RECORD] = Mix_LoadWAV("dat\\record.ogg");
}

static void loadMusic(void) {
	titleMusic = Mix_LoadMUS("dat\\title.ogg");
	strollMusic = Mix_LoadMUS("dat\\stroll.ogg");
	sprintMusic = Mix_LoadMUS("dat\\sprint.ogg");
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

void stopSound(int channel, int fadeOut) {
	Mix_FadeOutChannel(channel, fadeOut);
}

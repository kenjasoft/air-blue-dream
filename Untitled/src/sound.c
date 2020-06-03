#include "sound.h"

static void loadSounds(void);
static void loadMusic(void);
static int checkSounds(void);

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* titleMusic;
static Mix_Music* strollMusic;
static Mix_Music* sprintMusic;

int initSounds(void) {
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
	titleMusic = NULL;
	strollMusic = NULL;
	sprintMusic = NULL;
	loadSounds();
	loadMusic();
	if (checkSounds() < 0) return -1;
	Mix_Volume(CH_CROW, (int)(MIX_MAX_VOLUME * .75f));
	Mix_Volume(CH_PIGEON, (int)(MIX_MAX_VOLUME * .75f));
	Mix_Volume(CH_JUMP, (int)(MIX_MAX_VOLUME * .75f));
	Mix_VolumeMusic((int)(MIX_MAX_VOLUME * .75f));
	return 0;
}

static void loadSounds(void) {
	sounds[SND_CROW] = Mix_LoadWAV("dat\\0.abd");
	sounds[SND_PIGEON] = Mix_LoadWAV("dat\\1.abd");
	sounds[SND_JUMP] = Mix_LoadWAV("dat\\2.abd");
	sounds[SND_ASCEND] = Mix_LoadWAV("dat\\3.abd");
	sounds[SND_WIN] = Mix_LoadWAV("dat\\4.abd");
	sounds[SND_LOSE] = Mix_LoadWAV("dat\\5.abd");
	sounds[SND_RECORD] = Mix_LoadWAV("dat\\6.abd");
}

static void loadMusic(void) {
	titleMusic = Mix_LoadMUS("dat\\7.abd");
	strollMusic = Mix_LoadMUS("dat\\8.abd");
	sprintMusic = Mix_LoadMUS("dat\\9.abd");
}

int getSoundSizeAndVerify(const char* fileName) {
	char buffer[MAX_LINE_LENGTH];
	FILE* file = fopen(fileName, "r");
	int prev = ftell(file);
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	if (size < MAX_LINE_LENGTH) return -1;
	fseek(file, MAX_LINE_LENGTH, SEEK_SET);
	fread(buffer, 1, sizeof(buffer), file);
	for (int i = 0; i < sizeof(buffer); ++i) if (buffer[i] == '\0') buffer[i] = '0';
	buffer[sizeof(buffer) - 1] = '\0';
	if (!strstr(buffer, "ARTIST=quisseh") || !strstr(buffer, "ALBUM=air-blue dream") || !strstr(buffer, "DATE=2020")) return -1;
	fseek(file, prev, SEEK_SET);
	fclose(file);
	return size;
}

static int checkSounds(void) {
	for (int i = 0; i < SND_MAX; ++i) if (sounds[i] == NULL) return -1;
	if (titleMusic == NULL || strollMusic == NULL || sprintMusic == NULL) return -1;
	if (getSoundSizeAndVerify("dat\\0.abd") != SND_SIZE_CROW || getSoundSizeAndVerify("dat\\1.abd") != SND_SIZE_PIGEON ||
		getSoundSizeAndVerify("dat\\2.abd") != SND_SIZE_JUMP || getSoundSizeAndVerify("dat\\3.abd") != SND_SIZE_ASCEND ||
		getSoundSizeAndVerify("dat\\4.abd") != SND_SIZE_WIN || getSoundSizeAndVerify("dat\\5.abd") != SND_SIZE_LOSE ||
		getSoundSizeAndVerify("dat\\6.abd") != SND_SIZE_RECORD || getSoundSizeAndVerify("dat\\7.abd") != SND_SIZE_TITLE ||
		getSoundSizeAndVerify("dat\\8.abd") != SND_SIZE_STROLL || getSoundSizeAndVerify("dat\\9.abd") != SND_SIZE_SPRINT)
		return -1;
	return 0;
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

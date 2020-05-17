#include "init.h"

void initSDL(void) {
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	windowFlags = 0;

	game.debug = 0;
	game.map = 0;
	game.freeze = 0;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) exit(1);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) exit(1);
	Mix_AllocateChannels(MAX_SND_CHANNELS);

	game.window = SDL_CreateWindow("air-blue dream", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	game.renderer = SDL_CreateRenderer(game.window, -1, rendererFlags);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	SDL_GameController* controller = NULL;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) break;
		}
	}

	SDL_Cursor* cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
}

char* encryptDecrypt(char* str, const char* key)
{
	char* c = str;
	size_t len = strlen(key), i = 0;
	while (*c) {
		*c++ ^= key[i++ % len];
	}
	return str;
}

void loadHighScores(void) {
	for (int i = 0; i < 7; ++i) {
		strollTimeLog[i][T_SAVED] = i < 6 ? 50000 : 300000;
	}
	sprintTimeLog[T_SAVED] = 180000;
	char* str = readFile("dat\\t.dat");
	if (str == NULL) return;
	if (sscanf(encryptDecrypt(str, "lNSjPehYQpJshkrm"), "%dA%dI%dR%dB%dL%dU%dE%d",
		&strollTimeLog[0][T_SAVED], &strollTimeLog[1][T_SAVED], &strollTimeLog[2][T_SAVED],
		&strollTimeLog[3][T_SAVED], &strollTimeLog[4][T_SAVED], &strollTimeLog[5][T_SAVED],
		&strollTimeLog[6][T_SAVED], &sprintTimeLog[T_SAVED]) <= 0) return;
	for (int i = 0; i < 7; ++i) {
		strollTimeLog[i][T_SAVED] = min(strollTimeLog[i][T_SAVED], TIMER_LIMIT);
	}
	sprintTimeLog[T_SAVED] = min(sprintTimeLog[T_SAVED], TIMER_LIMIT);
}

void saveHighScores(void) {
	FILE* file = fopen("dat\\t.dat", "w");
	if (file == NULL) return;
	else {
		for (int i = 0; i < 7; ++i) {
			strollTimeLog[i][T_SAVED] = min(strollTimeLog[i][T_SAVED], TIMER_LIMIT);
		}
		sprintTimeLog[T_SAVED] = min(sprintTimeLog[T_SAVED], TIMER_LIMIT);
		char str[72];
		sprintf(str, "%dA%dI%dR%dB%dL%dU%dE%d",
			strollTimeLog[0][T_SAVED], strollTimeLog[1][T_SAVED], strollTimeLog[2][T_SAVED],
			strollTimeLog[3][T_SAVED], strollTimeLog[4][T_SAVED], strollTimeLog[5][T_SAVED],
			strollTimeLog[6][T_SAVED], sprintTimeLog[T_SAVED]);
		fputs(encryptDecrypt(str, "lNSjPehYQpJshkrm"), file);
		fclose(file);
	}
}

void initGame(void) {
	loadHighScores();
	loadTextures();

	//initSounds();
	//loadMusic("snd\\title.mp3");
	//playMusic(1);
}

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

void loadHighScores(void) {
	// TODO: load both arrays from file
	for (int i = 0; i < 7; ++i) {
		strollTimeLog[i][T_SAVED] = i < 6 ? 4567 : 98765;
	}
	sprintTimeLog[T_SAVED] = 300000;
}

void saveHighScores(void) {
	// TODO
}

void initGame(void) {
	loadHighScores();
	loadTextures();

	//initSounds();
	//loadMusic("snd\\title.mp3");
	//playMusic(1);
}

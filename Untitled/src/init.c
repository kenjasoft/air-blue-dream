#include "init.h"

void initSDL(void) {
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	windowFlags = 0;

	game.debug = 0;
	game.map = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) exit(1);
	Mix_AllocateChannels(MAX_SND_CHANNELS);

	game.window = SDL_CreateWindow("Untitled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	game.renderer = SDL_CreateRenderer(game.window, -1, rendererFlags);
	IMG_Init(IMG_INIT_PNG);

	SDL_Cursor* cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
}

void initGame(void) {
	loadTextures();

	//initSounds();
	//loadMusic("snd\\title.mp3");
	//playMusic(1);
}

void cleanup(void) {
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
	SDL_Quit();
}

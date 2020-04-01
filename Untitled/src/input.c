#include "input.h"

void doKeyUp(SDL_KeyboardEvent* event) {
	if (event->keysym.scancode < MAX_KEYBOARD_KEYS) game.keyboard[event->keysym.scancode][CUR] = 0;
}

void doKeyDown(SDL_KeyboardEvent* event) {
	if (event->keysym.scancode < MAX_KEYBOARD_KEYS) game.keyboard[event->keysym.scancode][CUR] = 1;

	if (event->keysym.scancode == SDL_SCANCODE_D) game.debug = game.debug ? 0 : 1;
	else if (event->keysym.scancode == SDL_SCANCODE_F) game.freeze = game.freeze ? 0 : 1;
	else if (event->keysym.scancode == SDL_SCANCODE_M) game.map = game.map ? 0 : 1;

	if (game.debug || game.freeze || game.map) SDL_ShowCursor(SDL_ENABLE);
	else SDL_ShowCursor(SDL_DISABLE);
}

void doInput(void) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
			doKeyDown(&event.key);
			break;

		case SDL_KEYUP:
			doKeyUp(&event.key);
			break;

		default:
			break;
		}
	}
}

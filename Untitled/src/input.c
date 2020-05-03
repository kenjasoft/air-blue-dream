#include "input.h"

void doKeyUp(SDL_KeyboardEvent* event) {
	if (event->keysym.scancode < MAX_KEYBOARD_KEYS) game.keyboard[event->keysym.scancode][CUR] = 0;
}

void doKeyDown(SDL_KeyboardEvent* event) {
	if (event->keysym.scancode < MAX_KEYBOARD_KEYS) game.keyboard[event->keysym.scancode][CUR] = 1;

	if (event->keysym.scancode == SDL_SCANCODE_D) game.debug = game.debug ? 0 : 1;
	else if (event->keysym.scancode == SDL_SCANCODE_F) game.freeze = game.freeze ? 0 : 1;
	else if (event->keysym.scancode == SDL_SCANCODE_M) game.map = game.map ? 0 : 1;

	if (game.debug || game.map) SDL_ShowCursor(SDL_ENABLE);
	else SDL_ShowCursor(SDL_DISABLE);
}

void doButton(SDL_ControllerButtonEvent* event, int upOrDown) {
	switch (event->button) {
	case SDL_CONTROLLER_BUTTON_A:
		game.keyboard[SDL_SCANCODE_Z][CUR] = upOrDown;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		game.keyboard[SDL_SCANCODE_DOWN][CUR] = upOrDown;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		game.keyboard[SDL_SCANCODE_UP][CUR] = upOrDown;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		game.keyboard[SDL_SCANCODE_LEFT][CUR] = upOrDown;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
		game.keyboard[SDL_SCANCODE_RIGHT][CUR] = upOrDown;
		break;
	default:
		break;
	}
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

		case SDL_CONTROLLERBUTTONDOWN:
			doButton(&event.cbutton, 1);
			break;

		case SDL_CONTROLLERBUTTONUP:
			doButton(&event.cbutton, 0);
			break;

		default:
			break;
		}
	}
}

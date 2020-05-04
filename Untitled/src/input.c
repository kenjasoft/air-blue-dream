#include "input.h"

void doKey(SDL_KeyboardEvent* event, int upOrDown) {
	switch (event->keysym.scancode) {
	case SDL_SCANCODE_LSHIFT:
	case SDL_SCANCODE_RSHIFT:
	case SDL_SCANCODE_LCTRL:
	case SDL_SCANCODE_RCTRL:
	case SDL_SCANCODE_SPACE:
	case SDL_SCANCODE_RETURN:
	case SDL_SCANCODE_Z:
	case SDL_SCANCODE_X:
	case SDL_SCANCODE_C:
	case SDL_SCANCODE_Q:
	case SDL_SCANCODE_E:
		game.keyboard[ACTION][CUR] = upOrDown;
		break;
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_W:
		game.keyboard[UP][CUR] = upOrDown;
		break;
	case SDL_SCANCODE_DOWN:
	case SDL_SCANCODE_S:
		game.keyboard[DOWN][CUR] = upOrDown;
		break;
	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_A:
		game.keyboard[LEFT][CUR] = upOrDown;
		break;
	case SDL_SCANCODE_RIGHT:
	case SDL_SCANCODE_D:
		game.keyboard[RIGHT][CUR] = upOrDown;
		break;

	case SDL_SCANCODE_1:
		if (upOrDown) game.debug = game.debug ? 0 : 1;
		break;
	case SDL_SCANCODE_2:
		if (upOrDown) game.map = game.map ? 0 : 1;
		break;
	case SDL_SCANCODE_3:
		if (upOrDown) game.freeze = game.freeze ? 0 : 1;
		break;
	case SDL_SCANCODE_4:
		game.keyboard[FLY][CUR] = upOrDown;
		break;

	default:
		break;
	}

	if (game.debug || game.map) SDL_ShowCursor(SDL_ENABLE);
	else SDL_ShowCursor(SDL_DISABLE);
}

void doButton(SDL_ControllerButtonEvent* event, int upOrDown) {
	switch (event->button) {
	case SDL_CONTROLLER_BUTTON_A:
	case SDL_CONTROLLER_BUTTON_B:
	case SDL_CONTROLLER_BUTTON_X:
	case SDL_CONTROLLER_BUTTON_Y:
		game.keyboard[ACTION][CUR] = upOrDown;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		game.keyboard[UP][CUR] = upOrDown;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		game.keyboard[DOWN][CUR] = upOrDown;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		game.keyboard[LEFT][CUR] = upOrDown;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
		game.keyboard[RIGHT][CUR] = upOrDown;
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
			doKey(&event.key, 1);
			break;
		case SDL_KEYUP:
			doKey(&event.key, 0);
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

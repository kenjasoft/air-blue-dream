#include "camera.h"

void doCamera(void) {
	if (!game.map) {
		stage.camera.xTarget = (int)player->x + (player->w / 2);
		stage.camera.yTarget = (int)player->y + (player->h / 2);

		stage.camera.xTarget -= (SCREEN_WIDTH / 2);
		stage.camera.yTarget -= (SCREEN_HEIGHT / 2);

		stage.camera.xTarget = min(max(stage.camera.xTarget, 0), (MAP_WIDTH * TILE_SIZE) - SCREEN_WIDTH);
		stage.camera.yTarget = min(max(stage.camera.yTarget, 0), (MAP_HEIGHT * TILE_SIZE) - SCREEN_HEIGHT);

		int x = abs(stage.camera.x - stage.camera.xTarget);
		if (stage.camera.x < stage.camera.xTarget) stage.camera.x = (int)(stage.camera.x + (.05f * (x + 19)));
		else if (stage.camera.x > stage.camera.xTarget) stage.camera.x = (int)(stage.camera.x - (.05f * x));

		int y = abs(stage.camera.y - stage.camera.yTarget);
		if (stage.camera.y < stage.camera.yTarget) stage.camera.y = (int)(stage.camera.y + (.05f * (y + 19)));
		else if (stage.camera.y > stage.camera.yTarget) stage.camera.y = (int)(stage.camera.y - (.05f * y));
	}
	else {
		if (stage.camera.x % 32 != 0) stage.camera.x = ((stage.camera.x / 32) + 1) * 32;
		if (stage.camera.y % 32 != 0) stage.camera.y = ((stage.camera.y / 32) + 1) * 32;

		if (game.keyboard[SDL_SCANCODE_LEFT][CUR]) stage.camera.x -= 32;
		if (game.keyboard[SDL_SCANCODE_RIGHT][CUR]) stage.camera.x += 32;
		if (game.keyboard[SDL_SCANCODE_UP][CUR]) stage.camera.y -= 32;
		if (game.keyboard[SDL_SCANCODE_DOWN][CUR]) stage.camera.y += 32;
	}
}

#include "camera.h"

void doCamera(void) {
	if (!game.map) {
		int y = stage.camera.y - stage.camera.yTarget;
		if (!stage.endCamera) {
			stage.camera.yTarget = (int)player->y + (player->h / 2);
			stage.camera.yTarget -= (SCREEN_HEIGHT / 2);
			stage.camera.yTarget = min(max(stage.camera.yTarget, 0), MAP_HEIGHT - SCREEN_HEIGHT);
			y = abs(stage.camera.y - stage.camera.yTarget);
		}
		if (stage.camera.y < stage.camera.yTarget) stage.camera.y = (int)(stage.camera.y + (.05f * (y + CAMERA_OFFSET)));
		else if (stage.camera.y > stage.camera.yTarget) stage.camera.y = (int)(stage.camera.y - (.05f * y));
	}
	else {
		if (stage.camera.y % 8 != 0) stage.camera.y = ((stage.camera.y / 8) + 1) * 8;
		if (game.keyboard[SDL_SCANCODE_UP][CUR]) stage.camera.y -= 8;
		else if (game.keyboard[SDL_SCANCODE_DOWN][CUR]) stage.camera.y += 8;
	}
}

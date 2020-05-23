#include "camera.h"

void doCamera(void) {
	if (stage.pauseSprint || stage.camera.y < -9999) return;
	if (!stage.isSprintMode || (stage.isSprintMode && !stage.isLevelReady) || (stage.isSprintMode && stage.endStage)) {
		int y = stage.camera.y - stage.camera.yTarget;
		if (!stage.endCamera) {
			if (stage.stageNumber == 0 && stage.camera.y == (MAP_HEIGHT - SCREEN_HEIGHT)) return;
			stage.camera.yTarget = (int)player->y + (player->h / 2);
			stage.camera.yTarget -= (SCREEN_HEIGHT / 2);
			stage.camera.yTarget = min(max(stage.camera.yTarget, 0), MAP_HEIGHT - SCREEN_HEIGHT);
			y = abs(stage.camera.y - stage.camera.yTarget);
		}
		if (stage.camera.y < stage.camera.yTarget) stage.camera.y = (int)(stage.camera.y + (.05f * (y + CAMERA_OFFSET)));
		else if (stage.camera.y > stage.camera.yTarget) stage.camera.y = (int)(stage.camera.y - (.05f * y));
	}
	else if (stage.isLevelReady && !stage.endStage) {
		if (stage.stageNumber > 4) stage.camera.y -= 2;
		else --stage.camera.y;
	}
}

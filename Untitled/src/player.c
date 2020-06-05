#include "player.h"

static SDL_Texture* playerIdle[4];
static SDL_Texture* playerWalk[6];

void initPlayer(char* line) {
	player = malloc(sizeof(Entity));
	if (player == NULL) return;
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;
	player->draw = 1;
	player->hp = 1;
	player->scaleX = 1;
	player->scaleY = 1;
	int facing = 0;
	if (sscanf(line, "%*s %f %f %d", &player->x, &player->y, &facing) <= 0) return;
	player->y += SCREEN_HEIGHT;
	playerIdle[0] = textures[TX_PLAYERIDLE1];
	playerIdle[1] = textures[TX_PLAYERIDLE2];
	playerIdle[2] = textures[TX_PLAYERIDLE3];
	playerIdle[3] = textures[TX_PLAYERIDLE4];
	playerWalk[0] = textures[TX_PLAYERWALK1];
	playerWalk[1] = textures[TX_PLAYERWALK2];
	playerWalk[2] = textures[TX_PLAYERWALK3];
	playerWalk[3] = textures[TX_PLAYERWALK4];
	player->texture = playerIdle[0];
	player->flip = facing ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
	player->flags = EF_PLAYER;
}

void doPlayer(void) {
	if (game.freeze) return;
	if (stage.isSprintMode && stage.isLevelReady && !stage.endStage && player->y > (stage.camera.y + SCREEN_HEIGHT + player->h)) {
		stopMusic(500);
		stage.timerFinish = stage.ticks;
		stage.winGame = stage.endStage = 1;
		stage.camera.yTarget += (int)(SCREEN_HEIGHT * 1.5);
		stage.endCamera = 1;
		stage.pauseSprint = 1;
		game.freeze = 1;
	}

	float cf = player->isOnGround ? .85f : .95f;
	float fx = .6f;
	int vx = 5;
	int vy = -15;
	int t = stage.ticks;
	int idleIndex = (t / 256) % 4;
	int runningIndex = (t / 64) % 4;

	if (player->dx > -(fx / 2) && player->dx < (fx / 2)) player->dx = 0;
	player->dx *= cf;

	player->texture = playerIdle[idleIndex];

	if (!stage.isLevelReady && stage.camera.y > 0 && stage.camera.y == stage.camera.yTarget) {
		stage.isLevelReady = 1;
		if (stage.stageNumber > 0 && (!stage.isSprintMode || (stage.isSprintMode && stage.timerStart == 0))) stage.timerStart = stage.ticks;
		if (stage.isSprintMode && stage.timerFinish > 0) stage.timerStart += (stage.ticks - stage.timerFinish);
	}
	if (!stage.isLevelReady) return;

	int isCrouching = game.keyboard[DOWN][CUR] && player->isOnGround && player->riding != NULL;
	if (isCrouching) player->texture = textures[TX_PLAYERCROUCH];

	if (game.keyboard[LEFT][CUR]) {
		player->texture = playerWalk[runningIndex];
		player->dx -= fx;
		player->dx = max(player->dx, -vx);
		if (!game.keyboard[RIGHT][CUR]) player->flip = SDL_FLIP_HORIZONTAL;
	}
	if (game.keyboard[RIGHT][CUR]) {
		player->texture = playerWalk[runningIndex];
		player->dx += fx;
		player->dx = min(player->dx, vx);
		if (!game.keyboard[LEFT][CUR]) player->flip = SDL_FLIP_NONE;
	}

	if (game.keyboard[ACTION][CUR]) {
		if (isCrouching && player->riding->flags & EF_PLATFORM) {
			playSound(SND_JUMP, CH_JUMP);
			++player->y;
		}
		else if (game.keyboard[ACTION][RPT] == 0 && player->isOnGround) {
			playSound(SND_JUMP, CH_JUMP);
			game.keyboard[ACTION][RPT] = 1;
			player->riding = NULL;
			player->dy = (float)vy;
			if (player->dx > fx) player->dx += 1;
			else if (player->dx < -fx) player->dx -= 1;
			player->texture = textures[TX_PLAYERJUMP];
		}
		else if (game.keyboard[ACTION][RPT] == 1 && !player->isOnGround) {
			player->dy *= 1.05f;
			player->texture = textures[TX_PLAYERJUMP];
		}
	}
	else {
		game.keyboard[ACTION][RPT] = 0;
	}
}

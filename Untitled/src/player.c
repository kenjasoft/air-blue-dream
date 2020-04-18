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
	float cf = player->isOnGround ? .85f : .95f;
	float fx = .6f;
	int vx = 5;
	int vy = -15;
	int t = SDL_GetTicks();
	int idleIndex = (t / 256) % 4;
	int runningIndex = (t / 64) % 4;

	if (player->dx > -(fx / 2) && player->dx < (fx / 2)) player->dx = 0;
	player->dx *= cf;

	player->texture = playerIdle[idleIndex];

	if (game.freeze || game.map) return;

	int isCrouching = game.keyboard[SDL_SCANCODE_DOWN][CUR] && player->isOnGround && player->riding != NULL;
	if (isCrouching) player->texture = textures[TX_PLAYERCROUCH];

	if (game.keyboard[SDL_SCANCODE_LEFT][CUR]) {
		player->texture = playerWalk[runningIndex];
		player->dx -= fx;
		player->dx = max(player->dx, -vx);
		player->flip = SDL_FLIP_HORIZONTAL;
	}
	else if (game.keyboard[SDL_SCANCODE_RIGHT][CUR]) {
		player->texture = playerWalk[runningIndex];
		player->dx += fx;
		player->dx = min(player->dx, vx);
		player->flip = SDL_FLIP_NONE;
	}

	if (game.keyboard[SDL_SCANCODE_Z][CUR]) {
		if (isCrouching && player->riding->flags & EF_PLATFORM) {
			++player->y;
		}
		else if (game.keyboard[SDL_SCANCODE_Z][RPT] == 0 && player->isOnGround) {
			game.keyboard[SDL_SCANCODE_Z][RPT] = 1;

			player->riding = NULL;
			player->dy = (float)vy;
			if (player->dx > fx) player->dx += 1;
			else if (player->dx < -fx) player->dx -= 1;

			player->texture = textures[TX_PLAYERJUMP];

			//playSound(SND_JUMP, CH_PLAYER);
		}
		else if (game.keyboard[SDL_SCANCODE_Z][RPT] == 1 && !player->isOnGround) {
			player->dy *= 1.05f;
			player->texture = textures[TX_PLAYERJUMP];
		}
	}
	else {
		game.keyboard[SDL_SCANCODE_Z][RPT] = 0;
	}
}

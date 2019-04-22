#include "player.h"

static SDL_Texture *playerTexture[2];

void initPlayer(void) {
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;

	player->hp = 1;
	player->x = 0;
	player->y = 400;
	playerTexture[0] = getTexture("img\\player1.png");
	playerTexture[1] = getTexture("img\\player2.png");
	player->texture = playerTexture[0];
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void doPlayer(void) {
	float cf = player->isOnGround ? .85f : .95f;
	float fx = .6f;
	int vx = 5;
	int vy = -15;

	if (player->dx > -(fx / 2) && player->dx < (fx / 2)) player->dx = 0;
	player->dx *= cf;

	if (game.map) return;

	if (game.keyboard[SDL_SCANCODE_LEFT][CUR]) {
		player->texture = playerTexture[1];
		player->dx -= fx;
		player->dx = max(player->dx, -vx);
	}

	if (game.keyboard[SDL_SCANCODE_RIGHT][CUR]) {
		player->texture = playerTexture[0];
		player->dx += fx;
		player->dx = min(player->dx, vx);
	}

	if (game.keyboard[SDL_SCANCODE_Z][CUR]) {
		if (game.keyboard[SDL_SCANCODE_DOWN][CUR] && player->isOnGround && player->riding != NULL && player->riding->flags & EF_PLATFORM) {
			++player->y;
		}
		else if (game.keyboard[SDL_SCANCODE_Z][RPT] == 0 && player->isOnGround) {
			game.keyboard[SDL_SCANCODE_Z][RPT] = 1;

			player->riding = NULL;
			player->dy = (float)vy;
			if (player->dx > fx) player->dx += 1;
			else if (player->dx < -fx) player->dx -= 1;

			//playSound(SND_JUMP, CH_PLAYER);
		}
		else if (game.keyboard[SDL_SCANCODE_Z][RPT] == 1 && !player->isOnGround) {
			player->dy *= 1.075f;
		}
	}
	else {
		game.keyboard[SDL_SCANCODE_Z][RPT] = 0;
	}
}

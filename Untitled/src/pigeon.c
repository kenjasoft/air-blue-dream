#include "pigeon.h"

static SDL_Texture* pigeonWalk[8];
static const float speed[3][2] = { {.6f, 20}, {.4f, 40} , {.0001f, 60} };

static void tick(void);
static void touch(Entity* other);

void initPigeon(char* line) {
	Entity* e;
	e = malloc(sizeof(Entity));
	if (e == NULL) return;
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	e->draw = 1;
	e->hp = 1;
	e->scaleX = 1;
	e->scaleY = 1;
	if (sscanf(line, "%*s %f %f", &e->x, &e->y) <= 0) return;
	e->y += SCREEN_HEIGHT;
	pigeonWalk[0] = textures[TX_PIGEONWALK1];
	pigeonWalk[1] = textures[TX_PIGEONWALK2];
	pigeonWalk[2] = textures[TX_PIGEONWALK3];
	pigeonWalk[3] = textures[TX_PIGEONWALK4];
	pigeonWalk[4] = textures[TX_PIGEONWALK5];
	pigeonWalk[5] = textures[TX_PIGEONWALK6];
	pigeonWalk[6] = textures[TX_PIGEONWALK7];
	pigeonWalk[7] = textures[TX_PIGEONWALK8];
	e->texture = pigeonWalk[0];
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_PIGEON;
	e->tick = tick;
	e->touch = touch;

	const int dir[2] = { -1, 1 };
	e->n = dir[rand() % 2];

	e->i[P_JUMP_COUNTER] = 0;
	e->i[P_JUMP_LIMIT] = (rand() % (500 - 100 + 1)) + 100;
	e->i[P_CAN_JUMP] = 0;

	int si = rand() % 3;
	e->f[0] = speed[si][0];
	e->i[P_ANIMATION_SPEED] = (int)speed[si][1];
}

static void touch(Entity* other) {
	if (other == player) {
		playSound(SND_PIGEON, CH_PIGEON);
		if (other->x > self->x) player->dx += 2;
		else if (other->x < self->x) player->dx -= 2;
		if (other->y > self->y) player->dy += 2;
		else if (other->y < self->y) player->dy -= 2;
	}
}

static void tick(void) {
	if (game.freeze) return;

	float fx = .4f;
	int vx = 4;
	int vy = -8;
	int t = stage.ticks;
	int runningIndex = (t / self->i[P_ANIMATION_SPEED]) % 8;
	int jump = self->i[P_JUMP_COUNTER] >= self->i[P_JUMP_LIMIT] && self->i[P_CAN_JUMP];

	if (self->dx > -(fx / 2) && self->dx < (fx / 2)) self->dx = 0;
	self->dx *= self->f[0];

	self->texture = pigeonWalk[runningIndex];

	if (self->y + self->h < stage.camera.y - self->h || self->y >(stage.camera.y + SCREEN_HEIGHT) + self->h) return;

	if (self->n == -1) {
		self->dx -= fx;
		self->dx = max(self->dx, -vx);
		self->flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		self->dx += fx;
		self->dx = min(self->dx, vx);
		self->flip = SDL_FLIP_NONE;
	}

	if (jump) {
		self->i[P_JUMP_COUNTER] = 0;
		self->i[P_JUMP_LIMIT] = (rand() % (500 - 100 + 1)) + 100;

		self->riding = NULL;
		self->dy = (float)vy;
		if (self->dx > fx) self->dx += 1;
		else if (self->dx < -fx) self->dx -= 1;

		int si = rand() % 3;
		self->f[0] = speed[si][0];
		self->i[P_ANIMATION_SPEED] = (int)speed[si][1];
	}
	self->i[P_JUMP_COUNTER]++;
}

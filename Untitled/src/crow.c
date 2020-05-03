#include "crow.h"

static SDL_Texture* crowFloat[4];

static void tick(void);
static void touch(Entity* other);

void initCrow(char* line) {
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
	// format: CROW x y xIsSin xFactor yIsSin yFactor
	if (sscanf(line, "%*s %f %f %d %f %d %f", &e->x, &e->y, &e->i[C_X_SIN], &e->f[C_X_FACTOR_MINOR], &e->i[C_Y_SIN], &e->f[C_Y_FACTOR_MINOR]) <= 0)
		return;
	e->y += SCREEN_HEIGHT;
	crowFloat[0] = textures[TX_CROWFLOAT1];
	crowFloat[1] = textures[TX_CROWFLOAT2];
	crowFloat[2] = textures[TX_CROWFLOAT3];
	crowFloat[3] = textures[TX_CROWFLOAT4];
	e->texture = crowFloat[0];
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_CROW + EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = touch;
	e->f[C_X_FACTOR_MAJOR] = 0;
	e->f[C_Y_FACTOR_MAJOR] = 0;
}

static void touch(Entity* other) {
	if (other == player) {
		if (other->x > self->x) player->dx += 2;
		else if (other->x < self->x) player->dx -= 2;
		if (other->y > self->y) player->dy += 2;
		else if (other->y < self->y) player->dy -= 2;
	}
}

static void tick(void) {
	if (game.freeze) return;

	int t = SDL_GetTicks();
	float oldX = self->x;

	int runningIndex = (t / 80) % 4;
	self->texture = crowFloat[runningIndex];

	if (self->y + self->h < stage.camera.y - self->h || self->y >(stage.camera.y + SCREEN_HEIGHT) + self->h) return;

	// format = x + y
	// sin(0.01f) + sin(0.01f) OR cos(0.01f) + cos(0.01f) == diagonal
	// sin(0.01f) + cos(0.01f) == circle
	// sin(0.1f) + cos(0.01f) == spiral up/down
	// sin(0.01f) + cos(0.1f) == usual spiral left/right
	self->f[C_X_FACTOR_MAJOR] += self->f[C_X_FACTOR_MINOR];
	self->f[C_Y_FACTOR_MAJOR] += self->f[C_Y_FACTOR_MINOR];
	self->x += self->i[C_X_SIN] ? sinf(self->f[C_X_FACTOR_MAJOR]) : cosf(self->f[C_X_FACTOR_MAJOR]);
	self->y += self->i[C_Y_SIN] ? sinf(self->f[C_Y_FACTOR_MAJOR]) : cosf(self->f[C_Y_FACTOR_MAJOR]);

	if (oldX > self->x) self->flip = SDL_FLIP_HORIZONTAL;
	else self->flip = SDL_FLIP_NONE;
}

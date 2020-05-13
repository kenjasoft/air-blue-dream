#include "light.h"

void initLight(float x, float y, float parentX, float parentY, int radius, int red, int green, int blue, int dir, int baseFreq, int baseSpeed);
static void tick(void);
double degreeToRadian(float deg);

void initLight(float x, float y, float parentX, float parentY, int radius, int red, int green, int blue, int dir, int baseFreq, int baseSpeed) {
	Entity* e;
	e = malloc(sizeof(Entity));
	if (e == NULL) return;
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	e->x = x;
	e->y = y;
	e->hp = 1;
	e->scaleX = 1;
	e->scaleY = 1;
	e->flip = SDL_FLIP_NONE;
	radius += rand() % 10;
	red += rand() % 50;
	green += rand() % 50;
	blue += rand() % 50;
	int dim = 3;
	e->texture = createLightParticle(game.renderer, radius, red, green, blue, dim);
	if (stage.stageNumber > 0) {
		fadeTexture(e->texture, -255);
		e->draw = 0;
	}
	else e->draw = 1;
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS + EF_LIGHT;
	e->tick = tick;

	int x2 = 0, y2 = 0, height = 0, amp = 0;
	if (dir == UP || dir == DOWN) {
		x2 = (int)((e->x + (e->w / 2)) - e->w / 14 + rand() % (e->w / 7));
		y2 = (int)(e->y + (dir == UP ? e->h : 0));
		height = e->h / 5 + rand() % (e->h * 4 / 5);
		amp = e->w * 5 / 28 + rand() % (e->w / 4);
	}
	else if (dir == LEFT || dir == RIGHT) {
		x2 = (int)(e->x + (dir == LEFT ? e->w : 0));
		y2 = (int)((e->y + (e->h / 2)) - e->h / 14 + rand() % (e->h / 7));
		height = e->w / 5 + rand() % (e->w * 4 / 5);
		amp = e->h * 5 / 28 + rand() % (e->h / 4);
	}

	int phase = rand() % 360;
	int freq = baseFreq + rand() % (baseFreq * 2);
	int speed = baseSpeed + rand() % baseSpeed;
	int i[] = { x2, y2, height, phase, amp, freq, speed, dir, 0, (int)parentX, (int)parentY };
	memcpy(e->i, i, sizeof(i));
}

static void tick(void) {
	if (self->n == 0) {}
	else if (self->n > 0) {
		self->draw = 1;
		if (fadeTexture(self->texture, self->n) == 255) self->n = 0;
	}
	else if (self->n < 0 && fadeTexture(self->texture, self->n) == 0) {
		self->draw = 0;
		self->n = 0;
	}

	int dx = 0, dy = 0;

	if (self->i[L_DIR] == UP || self->i[L_DIR] == DOWN) {
		dx = (int)(self->i[L_X] + SDL_sin(degreeToRadian((float)(self->i[L_ANGLE] + self->i[L_PHASE]))) * self->i[L_AMP]);
		dy = (int)(self->i[L_DIR] == UP ? (self->y + (self->h / 2)) - self->i[L_SPEED] : (self->y + (self->h / 2)) + self->i[L_SPEED]);

		if ((self->i[L_DIR] == UP ? self->i[L_Y] - (self->y + (self->h / 2)) : (self->y + (self->h / 2)) - self->i[L_Y]) >= self->i[L_HEIGHT]) {
			dx = self->i[L_X];
			dy = self->i[L_Y];
			self->i[L_ANGLE] = 0;
		}
	}
	else if (self->i[L_DIR] == LEFT || self->i[L_DIR] == RIGHT) {
		dy = (int)(self->i[L_Y] + SDL_sin(degreeToRadian((float)(self->i[L_ANGLE] + self->i[L_PHASE]))) * self->i[L_AMP]);
		dx = (int)(self->i[L_DIR] == LEFT ? (self->x + (self->w / 2)) - self->i[L_SPEED] : (self->x + (self->w / 2)) + self->i[L_SPEED]);

		if ((self->i[L_DIR] == LEFT ? self->i[L_X] - (self->x + (self->w / 2)) : (self->x + (self->w / 2)) - self->i[L_X]) >= self->i[L_HEIGHT]) {
			dx = self->i[L_X];
			dy = self->i[L_Y];
			self->i[L_ANGLE] = 0;
		}
	}

	self->x = dx - self->w / 2.f;
	self->y = dy - self->h / 2.f;
	self->i[L_ANGLE] += self->i[L_FREQ];
}

double degreeToRadian(float deg) {
	return (deg / 360) * 2.0 * 3.14159265358979;
}

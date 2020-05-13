#include "text.h"

static void tick(void);

void initText(char* line) {
	Entity* e;
	e = malloc(sizeof(Entity));
	if (e == NULL) return;
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	e->scaleX = 1;
	e->scaleY = 1;
	e->hit = 0;
	int type;
	if (sscanf(line, "%*s %f %f %d", &e->x, &e->y, &type) <= 0) return;
	e->y += SCREEN_HEIGHT;
	e->texture = textures[33 + type];
	e->hp = 1;
	e->draw = 1;
	e->n = (int)e->y;
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->f[C_Y_FACTOR_MAJOR] = 4.6f;
	e->f[C_Y_FACTOR_MINOR] = .2f;
}

static void tick(void) {
	if (self->n == (SCREEN_HEIGHT + MENU_1 - MENU_DIST) && stage.menu[0] ||
		self->n == (SCREEN_HEIGHT + MENU_2 - MENU_DIST) && stage.menu[1] ||
		self->n == (SCREEN_HEIGHT + MENU_3 - MENU_DIST) && stage.menu[2]) {
		if (self->hit == 0) {
			self->y -= 4;
			if (self->y <= self->n - 32) {
				self->hit = 1;
				self->f[C_Y_FACTOR_MAJOR] = 4.6f;
			}
		}
		else {
			self->f[C_Y_FACTOR_MAJOR] += self->f[C_Y_FACTOR_MINOR];
			self->y += cosf(self->f[C_Y_FACTOR_MAJOR]);
			if (self->n == (SCREEN_HEIGHT + MENU_1 - MENU_DIST) && stage.menu[0]) fadeTexture(textures[TX_TEXT7], 51);
			else if (self->n == (SCREEN_HEIGHT + MENU_2 - MENU_DIST) && stage.menu[1]) fadeTexture(textures[TX_TEXT8], 51);
		}
	}
	else {
		self->hit = 0;
		if ((int)self->y < self->n) {
			self->y += min(self->n - self->y, 4);
			if (self->n == (SCREEN_HEIGHT + MENU_1 - MENU_DIST)) fadeTexture(textures[TX_TEXT7], -51);
			if (self->n == (SCREEN_HEIGHT + MENU_2 - MENU_DIST)) fadeTexture(textures[TX_TEXT8], -51);
		}
	}
}

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
	int type;
	if (sscanf(line, "%*s %f %f %d", &e->x, &e->y, &type) <= 0) return;
	e->hit = 0;
	e->i[TYPE] = type;
	e->i[ALPHA] = 0;
	e->y += SCREEN_HEIGHT;
	if (type >= 0 && type < 7) e->texture = textures[TX_SUBTITLE + type];
	else if (type < 9) {
		char timestamp[20];
		int ms, min, sec, total, s;
		SDL_Surface* surface;
		total = type == 7 ? strollTimeLog[6][T_SAVED] : sprintTimeLog[T_SAVED];
		ms = total % 1000;
		s = total / 1000;
		min = s / 60;
		sec = s % 60;
		sprintf(timestamp, "best %02d:%02d.%03d", min, sec, ms);
		surface = TTF_RenderText_Blended(font24, timestamp, whiteColor);
		e->texture = SDL_CreateTextureFromSurface(game.renderer, surface);
		fadeTexture(e->texture, -255);
		SDL_FreeSurface(surface);
	}
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
	if (self->i[TYPE] < 3 || self->i[TYPE] == 6 || self->i[TYPE] > 8) return;
	if (self->i[TYPE] == MENU_1 && stage.menu[0] ||
		self->i[TYPE] == MENU_2 && stage.menu[1] ||
		self->i[TYPE] == MENU_3 && stage.menu[2]) {
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
		}
	}
	else {
		self->hit = 0;
		if ((int)self->y < self->n) self->y += min(self->n - self->y, 4);
		if (((self->i[TYPE] == 7 && stage.menu[0]) || (self->i[TYPE] == 8 && stage.menu[1])) && self->i[ALPHA] < 255) {
			self->i[ALPHA] = fadeTexture(self->texture, 51);
		}
		else if (((self->i[TYPE] == 7 && !stage.menu[0]) || (self->i[TYPE] == 8 && !stage.menu[1])) && self->i[ALPHA] > 0) {
			self->i[ALPHA] = fadeTexture(self->texture, -51);
		}
	}
}

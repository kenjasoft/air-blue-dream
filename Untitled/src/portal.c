#include "portal.h"

void initPortal(char *line);
static void tick(void);
static void touch(Entity *other);

void initPortal(char *line) {
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);
	e->hp = 1;
	e->n = 0; //maybe have an array of n
	e->flags = EF_PORTAL;
	e->texture = getTexture("img\\portal.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->tick = tick;
	e->touch = touch;
}

static void tick(void) {
	//self->n += .1f;
}

static void touch(Entity *other) {
	if (self->hp > 0 && other == player) {
		//activate
		//check if player presses up. if so, teleport
		//playSound(SND_PORTAL, CH_PORTAL);
	}
}

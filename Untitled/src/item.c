#include "item.h"

void initItem(char *line);
static void tick(void);
static void touch(Entity *other);

void initItem(char *line) {
	Entity *e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	sscanf(line, "%*s %f %f", &e->x, &e->y);
	e->hp = 1;
	e->draw = 1;
	e->texture = textures[TX_ITEM];
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_ITEM;
	e->tick = tick;
	e->touch = touch;
}

static void tick(void) {
	//update texture or position
}

static void touch(Entity *other) {
	if (self->hp > 0 && other == player) {
		self->hp = 0;
		//playSound(SND_ITEM, CH_ITEM);
	}
}

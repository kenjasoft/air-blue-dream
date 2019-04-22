#include "platform.h"

void initPlatform(char *line) {
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->hp = 1;

	e->texture = getTexture("img\\platform.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_PLATFORM + EF_WEIGHTLESS;
}

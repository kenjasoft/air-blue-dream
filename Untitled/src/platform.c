#include "platform.h"

void initPlatform(char* line) {
	Entity* e;
	e = malloc(sizeof(Entity));
	if (e == NULL) return;
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	e->scaleX = 1;
	e->scaleY = 1;
	char name[MAX_NAME_LENGTH] = { 0 };
	if (sscanf(line, "%s %f %f %d", name, &e->x, &e->y, &e->flip) <= 0) return;
	e->y += SCREEN_HEIGHT;
	e->hp = 1;
	e->draw = 1;
	if (strcmp(name, "ROCKPLATFORM") == 0) {
		e->texture = textures[TX_ROCKPLATFORM];
	}
	else if (strcmp(name, "GRASSPLATFORM") == 0) {
		e->texture = textures[TX_GRASSPLATFORM];
	}
	else if (strcmp(name, "SMALLROCKPLATFORM") == 0) {
		e->texture = textures[TX_SMALLROCKPLATFORM];
	}
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_PLATFORM + EF_WEIGHTLESS;
}

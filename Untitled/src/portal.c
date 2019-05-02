#include "portal.h"

void initPortal(char *line);
static void touch(Entity *other);

void initPortal(char *line) {
	Entity *e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	e->hit = 0;
	e->draw = 1;
	sscanf(line, "%*s %f %f", &e->x, &e->y);
	e->hp = 1;
	e->flags = EF_PORTAL;
	SDL_Texture* texture = NULL;
	texture = SDL_CreateTexture(game.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 48, 4);
	SDL_SetRenderTarget(game.renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 0);
	SDL_SetRenderTarget(game.renderer, NULL);
	e->texture = texture;
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->touch = touch;
	for (int i = 0; i < 20; ++i) {
		initLight(e->x - 20, e->y - 100, e->x, e->y, 40, 109, 194, 202, UP, 5, 1);
	}
}

static void touch(Entity *other) {
	if (other == player) {
		//check if player presses up. if so, teleport
		//playSound(SND_PORTAL, CH_PORTAL);
		self->hit = 1;
	}
}

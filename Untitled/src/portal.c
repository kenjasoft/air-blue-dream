#include "portal.h"

void initPortal(char* line);
static void touch(Entity* other);

void initPortal(char* line) {
	Entity* e;
	e = malloc(sizeof(Entity));
	if (e == NULL) return;
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	e->draw = 1;
	e->scaleX = 1;
	e->scaleY = 1;
	e->flip = SDL_FLIP_NONE;
	// put it 4 pixels above whatever platform it's on. 3rd parameter = 0 for hidden, 2 for visible
	if (sscanf(line, "%*s %f %f %d", &e->x, &e->y, &e->hit) <= 0) return;
	e->hp = 1;
	e->flags = EF_PORTAL;
	SDL_Texture* texture = NULL;
	texture = SDL_CreateTexture(game.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, PLAYER_WIDTH, 4);
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

static void touch(Entity* other) {
	if (other == player) {
		// check if player presses up. if so, teleport
		//playSound(SND_PORTAL, CH_PORTAL);
		if (self->hit != HIT_ALWAYS) self->hit = HIT_ON;
	}
}

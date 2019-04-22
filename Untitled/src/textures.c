#include "textures.h"

SDL_Texture *getTexture(char *name) {
	Texture *t;

	for (t = game.textureHead.next; t != NULL; t = t->next) {
		if (strcmp(t->name, name) == 0) return t->texture;
	}

	return NULL;
}

static void addTextureToCache(const char *name, SDL_Texture *sdlTexture) {
	Texture *texture;

	texture = malloc(sizeof(Texture));
	memset(texture, 0, sizeof(Texture));
	game.textureTail->next = texture;
	game.textureTail = texture;

	strncpy(texture->name, name, MAX_NAME_LENGTH);
	texture->texture = sdlTexture;
}

void loadTextures() {
	const char *names[] = {
		"img\\item.png",
		"img\\platform.png",
		"img\\player1.png",
		"img\\player2.png",
		"img\\portal.png",
		"img\\tile1.png",
		"img\\tile2.png",
		"img\\tile3.png"
	};
	int size = (sizeof(names) / sizeof(const char *));
	SDL_Texture *texture;
	for (int i = 0; i < size; ++i) {
		texture = IMG_LoadTexture(game.renderer, names[i]);
		addTextureToCache(names[i], texture);
	}
}

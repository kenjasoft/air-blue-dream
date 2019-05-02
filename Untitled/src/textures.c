#include "textures.h"

void loadTextures() {
	const char *names[] = {
		"img\\item.png",
		"img\\platform.png",
		"img\\player1.png",
		"img\\player2.png",
		"img\\tile1.png",
		"img\\tile2.png",
		"img\\tile3.png"
	};
	int size = (sizeof(names) / sizeof(const char *));
	for (int i = 0; i < size; ++i) {
		textures[i] = IMG_LoadTexture(game.renderer, names[i]);
	}
}

int fadeTexture(SDL_Texture* texture, int alpha) {
	SDL_BlendMode blend;
	Uint8 curAlpha = 0;

	SDL_GetTextureBlendMode(texture, &blend);
	SDL_GetTextureAlphaMod(texture, &curAlpha);

	if (blend != SDL_BLENDMODE_BLEND) {
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}

	alpha += curAlpha;
	if (alpha < 0) alpha = 0;
	if (alpha > 255) alpha = 255;

	SDL_SetTextureAlphaMod(texture, alpha);
	return alpha;
}

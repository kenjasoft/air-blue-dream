#include "textures.h"

void loadTextures() {
	const char* names[] = {
		"img\\playercrouch.png",
		"img\\playeridle1.png",
		"img\\playeridle2.png",
		"img\\playeridle3.png",
		"img\\playeridle4.png",
		"img\\playerjump.png",
		"img\\playerwalk1.png",
		"img\\playerwalk2.png",
		"img\\playerwalk3.png",
		"img\\playerwalk4.png",
		"img\\rockplatform.png",
		"img\\tree.png",
		"img\\ground.png",
		"img\\sky.png",
		"img\\landscape.png",
		"img\\bush.png",
		"img\\cloud1.png",
		"img\\cloud2.png",
		"img\\flowers.png",
		"img\\maple.png",
		"img\\grassplatform.png",
		"img\\smallrockplatform.png"
	};
	int size = (sizeof(names) / sizeof(const char*));
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

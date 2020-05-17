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
		"img\\smallrockplatform.png",
		"img\\pigeonwalk1.png",
		"img\\pigeonwalk2.png",
		"img\\pigeonwalk3.png",
		"img\\pigeonwalk4.png",
		"img\\pigeonwalk5.png",
		"img\\pigeonwalk6.png",
		"img\\pigeonwalk7.png",
		"img\\pigeonwalk8.png",
		"img\\crowfloat1.png",
		"img\\crowfloat2.png",
		"img\\crowfloat3.png",
		"img\\crowfloat4.png",
		"img\\subtitle.png"
	};
	int size = (sizeof(names) / sizeof(const char*));
	for (int i = 0; i < size; ++i) {
		textures[i] = IMG_LoadTexture(game.renderer, names[i]);
	}

	font24 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 24);
	font36 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 36);
	font48 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 48);
	font54 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 54);
	font72 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 72);
	font112 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 112);

	SDL_Surface* surface = TTF_RenderText_Blended(font72, "air-blue", whiteColor);
	textures[TX_TEXT1] = SDL_CreateTextureFromSurface(game.renderer, surface);
	surface = TTF_RenderText_Blended(font112, "dream", whiteColor);
	textures[TX_TEXT2] = SDL_CreateTextureFromSurface(game.renderer, surface);
	surface = TTF_RenderText_Blended(font48, "stroll", whiteColor);
	textures[TX_TEXT3] = SDL_CreateTextureFromSurface(game.renderer, surface);
	surface = TTF_RenderText_Blended(font48, "sprint", whiteColor);
	textures[TX_TEXT4] = SDL_CreateTextureFromSurface(game.renderer, surface);
	surface = TTF_RenderText_Blended(font48, "quit", whiteColor);
	textures[TX_TEXT5] = SDL_CreateTextureFromSurface(game.renderer, surface);
	surface = TTF_RenderText_Blended(font24, "© 2020 quisseh", whiteColor);
	textures[TX_TEXT6] = SDL_CreateTextureFromSurface(game.renderer, surface);
	SDL_FreeSurface(surface);
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

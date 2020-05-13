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
		"img\\crowfloat4.png"
	};
	int size = (sizeof(names) / sizeof(const char*));
	for (int i = 0; i < size; ++i) {
		textures[i] = IMG_LoadTexture(game.renderer, names[i]);
	}

	TTF_Font* font24 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 24);
	TTF_Font* font48 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 48);
	TTF_Font* font72 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 72);
	TTF_Font* font112 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 112);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Blended(font72, "air-blue", color);
	textures[TX_TEXT1] = SDL_CreateTextureFromSurface(game.renderer, textSurface);
	textSurface = TTF_RenderText_Blended(font112, "dream", color);
	textures[TX_TEXT2] = SDL_CreateTextureFromSurface(game.renderer, textSurface);
	textSurface = TTF_RenderText_Blended(font48, "stroll", color);
	textures[TX_TEXT3] = SDL_CreateTextureFromSurface(game.renderer, textSurface);
	textSurface = TTF_RenderText_Blended(font48, "sprint", color);
	textures[TX_TEXT4] = SDL_CreateTextureFromSurface(game.renderer, textSurface);
	textSurface = TTF_RenderText_Blended(font48, "quit", color);
	textures[TX_TEXT5] = SDL_CreateTextureFromSurface(game.renderer, textSurface);
	textSurface = TTF_RenderText_Blended(font24, "© 2020 quisseh", color);
	textures[TX_TEXT6] = SDL_CreateTextureFromSurface(game.renderer, textSurface);
	// TODO: need to rebuild these somewhere if they set a new record
	char timestamp[20];
	int ms[2], min[2], sec[2];
	int total = strollTimeLog[6][T_SAVED];
	ms[0] = total % 1000;
	int s = total / 1000;
	min[0] = s / 60;
	sec[0] = s % 60;
	total = sprintTimeLog[6][T_SAVED];
	ms[1] = total % 1000;
	s = total / 1000;
	min[1] = s / 60;
	sec[1] = s % 60;
	sprintf(timestamp, "best %02d:%02d.%03d", min[0], sec[0], ms[0]);
	textSurface = TTF_RenderText_Blended(font24, timestamp, color);
	textures[TX_TEXT7] = SDL_CreateTextureFromSurface(game.renderer, textSurface);
	fadeTexture(textures[TX_TEXT7], -255);
	sprintf(timestamp, "best %02d:%02d.%03d", min[1], sec[1], ms[1]);
	textSurface = TTF_RenderText_Blended(font24, timestamp, color);
	textures[TX_TEXT8] = SDL_CreateTextureFromSurface(game.renderer, textSurface);
	fadeTexture(textures[TX_TEXT8], -255);
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

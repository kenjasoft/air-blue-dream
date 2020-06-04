#include "textures.h"

void loadTextures() {
	SDL_RWops* rw = SDL_RWFromConstMem(playerCrouch, sizeof(playerCrouch));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERCROUCH] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerIdle1, sizeof(playerIdle1));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERIDLE1] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerIdle2, sizeof(playerIdle2));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERIDLE2] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerIdle3, sizeof(playerIdle3));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERIDLE3] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerIdle4, sizeof(playerIdle4));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERIDLE4] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerJump, sizeof(playerJump));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERJUMP] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerWalk1, sizeof(playerWalk1));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERWALK1] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerWalk2, sizeof(playerWalk2));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERWALK2] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerWalk3, sizeof(playerWalk3));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERWALK3] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(playerWalk4, sizeof(playerWalk4));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PLAYERWALK4] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(rockPlatform, sizeof(rockPlatform));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_ROCKPLATFORM] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(tree, sizeof(tree));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_TREE] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(ground, sizeof(ground));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_GROUND] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(sky, sizeof(sky));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_SKY] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(landscape, sizeof(landscape));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_LANDSCAPE] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(bush, sizeof(bush));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_BUSH] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(cloud1, sizeof(cloud1));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_CLOUD1] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(cloud2, sizeof(cloud2));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_CLOUD2] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(flowers, sizeof(flowers));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_FLOWERS] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(maple, sizeof(maple));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_MAPLE] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(grassPlatform, sizeof(grassPlatform));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_GRASSPLATFORM] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(smallRockPlatform, sizeof(smallRockPlatform));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_SMALLROCKPLATFORM] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(pigeonWalk1, sizeof(pigeonWalk1));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PIGEONWALK1] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(pigeonWalk2, sizeof(pigeonWalk2));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PIGEONWALK2] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(pigeonWalk3, sizeof(pigeonWalk3));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PIGEONWALK3] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(pigeonWalk4, sizeof(pigeonWalk4));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PIGEONWALK4] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(pigeonWalk5, sizeof(pigeonWalk5));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PIGEONWALK5] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(pigeonWalk6, sizeof(pigeonWalk6));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PIGEONWALK6] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(pigeonWalk7, sizeof(pigeonWalk7));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PIGEONWALK7] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(pigeonWalk8, sizeof(pigeonWalk8));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_PIGEONWALK8] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(crowFloat1, sizeof(crowFloat1));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_CROWFLOAT1] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(crowFloat2, sizeof(crowFloat2));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_CROWFLOAT2] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(crowFloat3, sizeof(crowFloat3));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_CROWFLOAT3] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(crowFloat4, sizeof(crowFloat4));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_CROWFLOAT4] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(subtitle, sizeof(subtitle));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	textures[TX_SUBTITLE] = SDL_CreateTextureFromSurface(game.renderer, IMG_LoadPNG_RW(rw));
	SDL_RWclose(rw);

	rw = SDL_RWFromConstMem(font, sizeof(font));
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	font24 = TTF_OpenFontRW(rw, 1, 24);
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	font36 = TTF_OpenFontRW(rw, 1, 36);
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	font48 = TTF_OpenFontRW(rw, 1, 48);
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	font54 = TTF_OpenFontRW(rw, 1, 54);
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	font72 = TTF_OpenFontRW(rw, 1, 72);
	SDL_RWseek(rw, 0, RW_SEEK_SET);
	font112 = TTF_OpenFontRW(rw, 1, 112);

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

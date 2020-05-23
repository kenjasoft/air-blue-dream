#include "draw.h"

void prepareScene(void) {
	SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
	SDL_RenderClear(game.renderer);
}

void presentScene(void) {
	SDL_RenderPresent(game.renderer);
}

void blit(SDL_Texture* texture, int x, int y, float scaleX, float scaleY, SDL_RendererFlip flip) {
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_RenderSetScale(game.renderer, scaleX, scaleY);
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopyEx(game.renderer, texture, NULL, &dest, 0, NULL, flip);
}

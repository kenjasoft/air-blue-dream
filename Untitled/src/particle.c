#include "particle.h"

static float getDistance(SDL_Point p1, SDL_Point p2) {
	int x = p2.x - p1.x;
	int y = p2.y - p1.y;
	float distance = (float)SDL_sqrt(x * x + y * y);
	return distance;
}

SDL_Texture *createLightParticle(SDL_Renderer* renderer, int radius, int red, int green, int blue, int dim) {
	float relativeDist = 0;
	float distance = 0;
	int alpha = 0;

	SDL_Point p = { 0, 0 };
	SDL_Point mid = { radius, radius };
	SDL_Texture* texture = NULL;

	if (dim < 0) dim = 4;

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, radius * 2, radius * 2);

	SDL_SetRenderTarget(renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	for (int y = 0; y < 2 * radius; y++) {
		for (int x = 0; x < 2 * radius; x++) {
			p.x = x;
			p.y = y;

			distance = getDistance(p, mid);

			if (distance <= radius) {
				relativeDist = distance / radius * dim + .5f;
				alpha = (int)(255 / (relativeDist * relativeDist) / 4);
			}
			else alpha = 0;

			SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}

	SDL_SetRenderTarget(renderer, NULL);

	return texture;
}

#include "stage.h"

static void logic(void);
static void draw(void);
static void drawDebug(void);

void initStage(void) {
	game.delegate.logic = logic;
	game.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));

	stage.entityTail = &stage.entityHead;

	initEntities();

	initPlayer();

	initMap();
}

static void logic(void) {
	doPlayer();

	doEntities();

	doCamera();
}

static void draw(void) {
	SDL_SetRenderDrawColor(game.renderer, 233, 127, 2, 255);
	SDL_RenderFillRect(game.renderer, NULL);

	if (game.debug || game.map) drawDebug();

	drawMap();

	drawEntities();
}

static void drawDebug(void) {
	if (game.map) {
		SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 102);
		for (int i = 0; i < SCREEN_WIDTH; i += 32) {
			SDL_RenderDrawLine(game.renderer, i, 0, i, SCREEN_HEIGHT);
		}
		for (int i = 0; i < SCREEN_HEIGHT; i += 32) {
			SDL_RenderDrawLine(game.renderer, 0, i, SCREEN_WIDTH, i);
		}
		SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_NONE);
	}
	int x, y;
	SDL_GetMouseState(&x, &y);
	printf("cur(%5d,%5d) pla(%5.0f,%5.0f) cam(x%5d xt%5d,y%5d yt%5d) vlc(%8.4f,%8.4f)\r",
		x + stage.camera.x, y + stage.camera.y, player->x, player->y, stage.camera.x, stage.camera.xTarget, stage.camera.y, stage.camera.yTarget, player->dx, player->dy);
}

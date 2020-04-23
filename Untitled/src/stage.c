#include "stage.h"

static void logic(void);
static void draw(void);
static void drawDebug(void);
static void initBackground(void);
static void drawBackground(void);

void initStage(void) {
	game.delegate.logic = logic;
	game.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.entityTail = &stage.entityHead;
	stage.stageNumber = 6;

	initBackground();
	initEntities();
}

static void logic(void) {
	doPlayer();
	doEntities();
	doCamera();
}

static void draw(void) {
	SDL_SetRenderDrawColor(game.renderer, 255, 196, 140, 255);
	SDL_RenderFillRect(game.renderer, NULL);

	drawBackground();
	drawEntities();

	if (game.debug || game.map) drawDebug();
}

static void drawDebug(void) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	printf("cur(%5d,%5d) pla(%5.0f,%5.0f) cam(x%5d xt%5d,y%5d yt%5d) vlc(%8.4f,%8.4f)\r",
		x + stage.camera.x, y + stage.camera.y, player->x, player->y, stage.camera.x, stage.camera.xTarget, stage.camera.y, stage.camera.yTarget, player->dx, player->dy);
}

static void initBackground(void) {
	for (int i = 0, x = -(SKY_WIDTH / 2) - 2; i < MAX_SKY; ++i, x += SKY_WIDTH / 2) {
		stage.sky[i] = (BareEntity*)malloc(sizeof(BareEntity));
		if (stage.sky == NULL) return;
		memset(stage.sky[i], 0, sizeof(BareEntity));
		stage.sky[i]->texture = textures[TX_SKY];
		stage.sky[i]->flip = i % 2 == 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
		stage.sky[i]->w = SKY_WIDTH;
		stage.sky[i]->h = SKY_HEIGHT;
		SDL_QueryTexture(stage.sky[i]->texture, NULL, NULL, &stage.sky[i]->w, &stage.sky[i]->h);
		stage.sky[i]->x = x + (i % 2 == 0 ? 1 : 0);
		stage.sky[i]->y = 0;
	}

	for (int i = 0; i < MAX_CLOUDS; ++i) {
		stage.clouds[i] = (BareEntity*)malloc(sizeof(BareEntity));
		if (stage.clouds == NULL) return;
		memset(stage.clouds[i], 0, sizeof(BareEntity));
		stage.clouds[i]->flip = SDL_FLIP_NONE;
	}
	stage.clouds[0]->texture = textures[TX_CLOUD1];
	stage.clouds[0]->w = CLOUD1_WIDTH;
	stage.clouds[0]->h = CLOUD1_HEIGHT;
	SDL_QueryTexture(stage.clouds[0]->texture, NULL, NULL, &stage.clouds[0]->w, &stage.clouds[0]->h);
	stage.clouds[0]->x = -18;
	stage.clouds[0]->y = 22;
	stage.clouds[1]->texture = textures[TX_CLOUD2];
	stage.clouds[1]->w = CLOUD2_WIDTH;
	stage.clouds[1]->h = CLOUD2_HEIGHT;
	SDL_QueryTexture(stage.clouds[1]->texture, NULL, NULL, &stage.clouds[1]->w, &stage.clouds[1]->h);
	stage.clouds[1]->x = 26;
	stage.clouds[1]->y = 2;
	stage.clouds[2]->texture = textures[TX_CLOUD1];
	stage.clouds[2]->w = CLOUD1_WIDTH;
	stage.clouds[2]->h = CLOUD1_HEIGHT;
	SDL_QueryTexture(stage.clouds[2]->texture, NULL, NULL, &stage.clouds[2]->w, &stage.clouds[2]->h);
	stage.clouds[2]->x = 78;
	stage.clouds[2]->y = 14;

	for (int i = 0, x = 0; i < MAX_LANDSCAPE; ++i, x += LANDSCAPE_WIDTH) {
		stage.landscape[i] = (BareEntity*)malloc(sizeof(BareEntity));
		if (stage.landscape == NULL) return;
		memset(stage.landscape[i], 0, sizeof(BareEntity));
		stage.landscape[i]->texture = textures[TX_LANDSCAPE];
		stage.landscape[i]->flip = SDL_FLIP_NONE;
		stage.landscape[i]->w = LANDSCAPE_WIDTH;
		stage.landscape[i]->h = LANDSCAPE_HEIGHT;
		SDL_QueryTexture(stage.landscape[i]->texture, NULL, NULL, &stage.landscape[i]->w, &stage.landscape[i]->h);
		stage.landscape[i]->x = x;
		stage.landscape[i]->y = ((SCREEN_HEIGHT / 2) - LANDSCAPE_HEIGHT);
	}
}

static void drawBackground(void) {
	for (int i = 0; i < MAX_SKY; ++i) {
		blit(stage.sky[i]->texture, stage.sky[i]->x, stage.sky[i]->y, 2, 2, stage.sky[i]->flip);
	}
	for (int i = 0; i < MAX_CLOUDS; ++i) {
		blit(stage.clouds[i]->texture, stage.clouds[i]->x, stage.clouds[i]->y, 3, 3, stage.clouds[i]->flip);
	}
	for (int i = 0; i < MAX_LANDSCAPE; ++i) {
		blit(stage.landscape[i]->texture, stage.landscape[i]->x, stage.landscape[i]->y, 2, 2, stage.landscape[i]->flip);
	}
}

#include "stage.h"

static void logic(void);
static void draw(void);
static void drawDebug(void);
static void initBackground(void);
static void drawBackground(void);
void doEndStage(void);
void slideText(int i, float* y, float* yTarget, float yTargetNew);

TTF_Font* font72;
TTF_Font* font54;
TTF_Font* font36;
SDL_Color color = { 255, 255, 255 };

void initStage(void) {
	game.delegate.logic = logic;
	game.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.entityTail = &stage.entityHead;
	stage.playerAlpha = 0;
	stage.stageNumber = 1;
	stage.holdTextScreen = 0;
	stage.endTimer = 50;
	stage.endCamera = 0;
	stage.endStage = 0;
	stage.showTextScreen = 0;
	stage.newRecord = 1; // TODO

	initBackground();
	initEntities();
}

static void logic(void) {
	doPlayer();
	doEntities();
	doCamera();
	if (stage.endStage) doEndStage();
}

void slideText(int i, float* y, float* yTarget, float yTargetNew) {
	int slideVal = (int)(.05f * (abs((int)(*y - *yTarget)) + CAMERA_OFFSET));
	if (*y == *yTarget) {
		if (i == 0) --stage.endTimer;
		if (stage.endTimer == 0) *yTarget = yTargetNew;
	}
	else if (*y < *yTarget) *y = (*y + slideVal);
	else *y = (*y - slideVal);
}

void doEndStage(void) {
	if (!stage.endCamera && stage.camera.y == stage.camera.yTarget) {
		stage.endCamera = 1;
	}
	else if (stage.playerAlpha >= 0 && (stage.playerAlpha = fadeTexture(player->texture, -5)) >= 0) {
		if (stage.playerAlpha % 2 == 0) stage.camera.yTarget -= 1;
		if (stage.playerAlpha == 0) stage.playerAlpha = -1;
	}
	else if (!stage.holdTextScreen && stage.endTimer > 0) {
		--stage.endTimer;
		if (stage.endTimer == 0) {
			stage.camera.yTarget -= (int)(SCREEN_HEIGHT * 1.5);
			stage.showTextScreen = 1;
		}
		else stage.camera.yTarget -= 4;
	}
	else if (!stage.holdTextScreen && stage.camera.y == (stage.camera.yTarget + CAMERA_OFFSET)) {
		stage.endTimer = 300;
		fadeTexture(player->texture, 255);
		for (Entity* e = stage.entityHead.next; e != NULL; e = e->next) {
			e->hp = 0;
		}
		stage.holdTextScreen = 1;
		// TODO: set up the time textures
	}
	else if (stage.holdTextScreen) {
		for (int i = 0; i < MAX_CLEAR_TEXT; ++i) {
			if (stage.clearText[i] == NULL || i == 1) continue;
			slideText(i, &stage.clearText[i]->y, &stage.clearText[i]->yTarget, textPositions[i][UPPER]);
		}
		if (stage.clearText[0] != NULL && stage.clearText[0]->y == stage.clearText[0]->yTarget) {
			if (stage.endTimer <= 298 && stage.endTimer > 17) fadeTexture(stage.clearText[1]->texture, 15);
			else if (stage.endTimer <= 17 && stage.endTimer > 0) fadeTexture(stage.clearText[1]->texture, -15);
			else if (stage.endTimer == 0) {
				stage.entityTail = &stage.entityHead;
				if (stage.stageNumber < 6) ++stage.stageNumber;
				else {
					// TODO: end the game
				}
				initEntities();
				stage.camera.y = levelTop[stage.stageNumber - 1] - PLAYER_HEIGHT - (SCREEN_HEIGHT / 2);
				stage.playerAlpha = 0;
				stage.holdTextScreen = 0;
				stage.showTextScreen = 0;
				stage.endTimer = 50;
				stage.endStage = 0;
				stage.endCamera = 0;
				stage.newRecord = 0;
				for (int i = 0; i < MAX_CLEAR_TEXT; ++i) {
					if (stage.clearText[i] == NULL) continue;
					stage.clearText[i]->yTarget = textPositions[i][LOWER];
				}
				stage.clearText[1]->y = textPositions[1][LOWER];
				game.freeze = 0;
			}
		}
	}
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
		stage.sky[i]->x = (float)(x + (i % 2 == 0 ? 1 : 0));
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
		stage.landscape[i]->x = (float)x;
		stage.landscape[i]->y = ((SCREEN_HEIGHT / 2) - LANDSCAPE_HEIGHT);
	}

	font72 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 72);
	font54 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 54);
	font36 = TTF_OpenFont("font\\CabinSketch-Bold.ttf", 36);

	SDL_Surface* surfaceClear = TTF_RenderText_Blended(font72, "CLEAR", color);
	SDL_Texture* textureClear = SDL_CreateTextureFromSurface(game.renderer, surfaceClear);
	stage.clearText[0] = (BareEntity*)malloc(sizeof(BareEntity));
	if (stage.clearText[0] == NULL) return;
	memset(stage.clearText[0], 0, sizeof(BareEntity));
	stage.clearText[0]->texture = textureClear;
	stage.clearText[0]->w = surfaceClear->w;
	stage.clearText[0]->h = surfaceClear->h;
	SDL_QueryTexture(stage.clearText[0]->texture, NULL, NULL, &stage.clearText[0]->w, &stage.clearText[0]->h);
	stage.clearText[0]->x = 94;
	stage.clearText[0]->y = textPositions[0][UPPER];
	stage.clearText[0]->yTarget = textPositions[0][LOWER];

	surfaceClear = TTF_RenderText_Blended(font54, "NEW RECORD", color);
	textureClear = SDL_CreateTextureFromSurface(game.renderer, surfaceClear);
	stage.clearText[1] = (BareEntity*)malloc(sizeof(BareEntity));
	if (stage.clearText[1] == NULL) return;
	memset(stage.clearText[1], 0, sizeof(BareEntity));
	stage.clearText[1]->texture = textureClear;
	stage.clearText[1]->w = surfaceClear->w;
	stage.clearText[1]->h = surfaceClear->h;
	SDL_QueryTexture(stage.clearText[1]->texture, NULL, NULL, &stage.clearText[1]->w, &stage.clearText[1]->h);
	stage.clearText[1]->x = 31;
	stage.clearText[1]->y = textPositions[1][UPPER];
	stage.clearText[1]->yTarget = textPositions[1][LOWER];
	fadeTexture(stage.clearText[1]->texture, -255);

	surfaceClear = TTF_RenderText_Blended(font36, "your time", color);
	textureClear = SDL_CreateTextureFromSurface(game.renderer, surfaceClear);
	stage.clearText[2] = (BareEntity*)malloc(sizeof(BareEntity));
	if (stage.clearText[2] == NULL) return;
	memset(stage.clearText[2], 0, sizeof(BareEntity));
	stage.clearText[2]->texture = textureClear;
	stage.clearText[2]->w = surfaceClear->w;
	stage.clearText[2]->h = surfaceClear->h;
	SDL_QueryTexture(stage.clearText[2]->texture, NULL, NULL, &stage.clearText[2]->w, &stage.clearText[2]->h);
	stage.clearText[2]->x = 17;
	stage.clearText[2]->y = textPositions[2][UPPER];
	stage.clearText[2]->yTarget = textPositions[2][LOWER];

	surfaceClear = TTF_RenderText_Blended(font36, "your best", color);
	textureClear = SDL_CreateTextureFromSurface(game.renderer, surfaceClear);
	stage.clearText[3] = (BareEntity*)malloc(sizeof(BareEntity));
	if (stage.clearText[3] == NULL) return;
	memset(stage.clearText[3], 0, sizeof(BareEntity));
	stage.clearText[3]->texture = textureClear;
	stage.clearText[3]->w = surfaceClear->w;
	stage.clearText[3]->h = surfaceClear->h;
	SDL_QueryTexture(stage.clearText[3]->texture, NULL, NULL, &stage.clearText[3]->w, &stage.clearText[3]->h);
	stage.clearText[3]->x = 17;
	stage.clearText[3]->y = textPositions[3][UPPER];
	stage.clearText[3]->yTarget = textPositions[3][LOWER];
}

static void drawBackground(void) {
	for (int i = 0; i < MAX_SKY; ++i) {
		blit(stage.sky[i]->texture, (int)stage.sky[i]->x, (int)stage.sky[i]->y, 2, 2, stage.sky[i]->flip);
	}
	for (int i = 0; i < MAX_CLOUDS; ++i) {
		blit(stage.clouds[i]->texture, (int)stage.clouds[i]->x, (int)stage.clouds[i]->y, 3, 3, stage.clouds[i]->flip);
	}
	for (int i = 0; i < MAX_LANDSCAPE; ++i) {
		blit(stage.landscape[i]->texture, (int)stage.landscape[i]->x, (int)stage.landscape[i]->y, 2, 2, stage.landscape[i]->flip);
	}
	if (stage.showTextScreen) {
		// TODO: maybe flip the text back and forth as it scrolls in and stop when it stops scrolling
		// TODO: make the time in this format: 1:12.123
		for (int i = 0; i < MAX_CLEAR_TEXT; ++i) {
			if (stage.clearText[i] == NULL) continue;
			if (i == 1 && stage.holdTextScreen) {
				stage.clearText[i]->f += .3f;
				stage.clearText[i]->y += sinf(stage.clearText[i]->f);
			}
			if (!(i == 1 && !stage.newRecord)) blit(stage.clearText[i]->texture, (int)stage.clearText[i]->x, (int)stage.clearText[i]->y, 1, 1, SDL_FLIP_NONE);
		}
	}
}

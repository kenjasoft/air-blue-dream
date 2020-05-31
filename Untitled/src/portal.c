#include "portal.h"

void initPortal(char* line);
static void touch(Entity* other);

void initPortal(char* line) {
	Entity* e;
	e = malloc(sizeof(Entity));
	if (e == NULL) return;
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	e->draw = 1;
	e->scaleX = 1;
	e->scaleY = 1;
	e->flip = SDL_FLIP_NONE;
	if (sscanf(line, "%*s %f %f %d", &e->x, &e->y, &e->hit) <= 0) return;
	e->y += SCREEN_HEIGHT;
	e->hp = 1;
	e->flags = EF_PORTAL + EF_WEIGHTLESS;
	SDL_Texture* texture = NULL;
	texture = SDL_CreateTexture(game.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, PLAYER_WIDTH, 4);
	SDL_SetRenderTarget(game.renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 0);
	SDL_SetRenderTarget(game.renderer, NULL);
	e->texture = texture;
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->touch = touch;
	for (int i = 0; i < 20; ++i) {
		initLight(e->x - 20, e->y - 100, e->x, e->y, 40, 109, 194, 202, UP, 5, 1);
	}
}

static void touch(Entity* other) {
	if (other == player) {
		if (!other->isOnGround || !((int)(other->y + other->h) == (int)(self->y + self->h))) return;
		if (self->hit != HIT_ALWAYS) self->hit = HIT_ON;
		if (stage.stageNumber == 0 && stage.isLevelReady) {
			switch ((int)self->y) {
			case MENU_1_Y + SCREEN_HEIGHT:
				stage.menu[0] = 1;
				break;
			case MENU_2_Y + SCREEN_HEIGHT:
				stage.menu[1] = 1;
				break;
			case MENU_3_Y + SCREEN_HEIGHT:
				stage.menu[2] = 1;
				break;
			default:
				break;
			}
			if (game.keyboard[UP][CUR]) {
				stopMusic(2500);
				playSound(SND_ASCEND, CH_ASCEND);
				game.freeze = 1;
				stage.endStage = 1;
			}
		}
		else if (game.keyboard[UP][CUR] && other->y < PORTAL_CUTOFF) {
			playSound(SND_ASCEND, CH_ASCEND);
			game.freeze = 1;
			stage.endStage = 1;
			stage.timerFinish = stage.ticks;
		}
	}
}

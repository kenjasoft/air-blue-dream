#include "entity.h"

static void move(Entity* e);
static void push(Entity* e, float dx, float dy);
static void moveToEntities(Entity* e, float dx, float dy);
static void loadEntities(const char* filename);
static void addEntityFromLine(char* line);

void initEntities(void) {
	char fileName[MAX_FILENAME_LENGTH];
	sprintf(fileName, "dat\\%d.dat", stage.stageNumber);
	loadEntities(fileName);
}

void initEntity(char* line) {
	Entity* e;

	e = malloc(sizeof(Entity));
	if (e == NULL) return;
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	char name[MAX_NAME_LENGTH] = { 0 };
	if (sscanf(line, "%s %f %f %d", name, &e->x, &e->y, &e->flip) <= 0) return;

	e->scaleX = 1;
	e->scaleY = 1;
	e->hp = 1;
	e->draw = 1;

	if (strcmp(name, "TREE") == 0) {
		e->texture = textures[TX_TREE];
		e->flags = EF_WEIGHTLESS;
	}
	else if (strcmp(name, "FLOWERS") == 0) {
		e->texture = textures[TX_FLOWERS];
		e->flags = EF_WEIGHTLESS;
	}
	else if (strcmp(name, "BUSH") == 0) {
		e->texture = textures[TX_BUSH];
		e->flags = EF_WEIGHTLESS;
	}
	else if (strcmp(name, "MAPLE") == 0) {
		e->texture = textures[TX_MAPLE];
		e->flags = EF_WEIGHTLESS;
	}
	else if (strcmp(name, "GROUND") == 0) {
		e->texture = textures[TX_GROUND];
		e->flags = EF_GROUND + EF_WEIGHTLESS;
	}
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
}

static void addEntityFromLine(char* line) {
	char name[MAX_NAME_LENGTH] = { 0 };

	if (sscanf(line, "%s", name) <= 0) return;
	if (strstr(name, "PLATFORM")) {
		initPlatform(line);
	}
	else if (strcmp(name, "PLAYER") == 0) {
		initPlayer(line);
	}
	else if (strcmp(name, "PIGEON") == 0) {
		initPigeon(line);
	}
	else if (strcmp(name, "CROW") == 0) {
		initCrow(line);
	}
	else if (strcmp(name, "PORTAL") == 0) {
		initPortal(line);
	}
	else {
		initEntity(line);
	}
}

static void loadEntities(const char* filename) {
	char line[MAX_LINE_LENGTH];
	char* data, * p;
	int n = 0;

	data = readFile(filename);
	p = data;
	memset(line, '\0', MAX_LINE_LENGTH);
	while (*p) {
		if (*p == '\n') {
			addEntityFromLine(line);
			memset(line, '\0', MAX_LINE_LENGTH);
			n = 0;
		}
		else line[n++] = *p;
		p++;
	}
	free(data);
}

void doEntities(void) {
	Entity* e, * prev;
	prev = &stage.entityHead;
	float portalX = 0, portalY = 0;

	for (e = stage.entityHead.next; e != NULL; e = e->next) {
		self = e;
		if (e->flags & EF_PORTAL && e->hit) {
			portalX = e->x;
			portalY = e->y;
			if (e->hit != HIT_ALWAYS) e->hit = HIT_OFF;
		}
		if (e->draw) {
			if (e->tick) e->tick();
			move(e);
		}
		if (e->hp <= 0) {
			if (e == stage.entityTail) stage.entityTail = prev;
			prev->next = e->next;
			free(e);
			e = prev;
		}
		prev = e;
	}

	for (e = stage.entityHead.next; e != NULL; e = e->next) {
		if (e->draw) {
			if (e->flags & EF_LIGHT && !(portalX == e->i[L_PARENT_X] && portalY == e->i[L_PARENT_Y])) {
				e->n = -5;
			}
			if (e->riding != NULL) {
				e->x += e->riding->dx;
				push(e, e->riding->dx, 0);
			}
			if (e->flags & EF_PLAYER) {
				if (e->x < -e->w) e->x = MAP_WIDTH;
				else if (e->x > MAP_WIDTH) e->x = (float)-e->w;
			}
		}
		else if (e->flags & EF_LIGHT && (portalX == e->i[L_PARENT_X] && portalY == e->i[L_PARENT_Y])) {
			e->draw = 1;
			e->n = 5;
		}
	}
}

static void move(Entity* e) {
	if (!(e->flags & EF_WEIGHTLESS)) {
		e->dy += 1.5;
		e->dy = max(min(e->dy, 18), -999);
	}
	if (e->riding != NULL && e->riding->dy > 0) {
		e->dy = e->riding->dy + 1;
	}

	e->riding = NULL;
	e->isOnGround = 0;

	e->x += e->dx;
	push(e, e->dx, 0);

	e->y += e->dy;
	push(e, 0, e->dy);
}

static void push(Entity* e, float dx, float dy) {
	moveToEntities(e, dx, dy);
}

static int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return (max(x1, x2) < min(x1 + w1, x2 + w2)) && (max(y1, y2) < min(y1 + h1, y2 + h2));
}

static void moveToEntities(Entity* e, float dx, float dy) {
	Entity* other;
	int adj;

	for (other = stage.entityHead.next; other != NULL; other = other->next) {
		if (other == e) continue;
		if ((other->flags & EF_PLATFORM || other->flags & EF_GROUND) && (e->flags & EF_PLAYER || e->flags & EF_PIGEON) &&
			collision((int)e->x + 18, (int)e->y, e->w - 18, e->h, (int)other->x + 18, (int)other->y, other->w - 18, other->h)) {
			if (dy != 0 && (int)((e->y - e->dy) + e->h) <= other->y) {
				adj = dy > 0 ? -e->h : other->h;
				e->y = other->y + adj;
				e->dy = 0;
				if (dy > 0) {
					e->isOnGround = 1;
					e->riding = other;
				}
			}
			if (e->flags & EF_PIGEON) {
				if (((e->x + e->w) + 2 >= (other->x + other->w) && e->n == 1)) {
					e->n = -1;
				}
				else if (((e->x) - 2 <= (other->x) && e->n == -1)) {
					e->n = 1;
				}
				if (((e->x + e->w) + 18 >= (other->x + other->w) && e->n == 1) || ((e->x) - 18 <= (other->x) && e->n == -1)) {
					e->i[P_CAN_JUMP] = 0;
				}
				else e->i[P_CAN_JUMP] = 1;
			}
		}
		else if (other->flags & EF_PLAYER && (e->flags & EF_PIGEON || e->flags & EF_CROW) &&
			collision((int)e->x + 18, (int)e->y + 18, e->w - 18, e->h - 18, (int)other->x + 18, (int)other->y + 18, other->w - 18, other->h - 18)) {
			if (e->touch) e->touch(other);
		}
		else if (other->flags & EF_PLAYER && e->flags & EF_PORTAL) {
			if (collision((int)e->x, (int)e->y, e->w, e->h, (int)other->x, (int)other->y, other->w, other->h) && e->touch) e->touch(other);
			if ((other->y > MAP_HEIGHT) && e->y > 2800) {
				other->x = e->x;
				other->y = e->y - (PLAYER_HEIGHT * 2);
			}
		}
	}
}

void drawEntities(void) {
	Entity* e;

	for (e = stage.entityHead.next; e != NULL; e = e->next) {
		if (e->y + e->h < stage.camera.y - e->h || e->y >(stage.camera.y + SCREEN_HEIGHT) + e->h) continue;
		if (e->draw) {
			if (e->flags & EF_PLATFORM || e->flags & EF_GROUND) {
				blit(e->texture, (int)(e->x - stage.camera.x), (int)((e->y - stage.camera.y) - 8), e->scaleX, e->scaleY, e->flip);
			}
			else blit(e->texture, (int)(e->x - stage.camera.x), (int)(e->y - stage.camera.y), e->scaleX, e->scaleY, e->flip);
		}
	}
}

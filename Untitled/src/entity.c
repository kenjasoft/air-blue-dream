#include "entity.h"

static void move(Entity *e);
static void push(Entity *e, float dx, float dy);
static void moveToWorld(Entity *e, float dx, float dy);
static void moveToEntities(Entity *e, float dx, float dy);
static void loadEnts(const char *filename);
static void addEntFromLine(char *line);

void initEntities(void) {
	loadEnts("dat\\e1.dat");
}

static void addEntFromLine(char *line) {
	char name[MAX_NAME_LENGTH];

	sscanf(line, "%s", name);

	if (strcmp(name, "PLATFORM") == 0) {
		initPlatform(line);
	}
	else if (strcmp(name, "PLAYER") == 0) {
		initPlayer(line);
	}
	else if (strcmp(name, "PORTAL") == 0) {
		initPortal(line);
	}
}

static void loadEnts(const char *filename) {
	char line[MAX_LINE_LENGTH];
	char *data, *p;
	int n = 0;

	data = readFile(filename);
	p = data;

	memset(line, '\0', MAX_LINE_LENGTH);

	while (*p) {
		if (*p == '\n') {
			addEntFromLine(line);
			memset(line, '\0', MAX_LINE_LENGTH);
			n = 0;
		}
		else {
			line[n++] = *p;
		}

		p++;
	}

	free(data);
}

void doEntities(void) {
	Entity *e, *prev;
	prev = &stage.entityHead;
	float portalX = 0, portalY = 0;

	for (e = stage.entityHead.next; e != NULL; e = e->next) {
		self = e;

		if (e->flags & EF_PORTAL && e->hit) {
			portalX = e->x;
			portalY = e->y;
			e->hit = 0;
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
			e->x = min(max(e->x, 0), MAP_WIDTH * TILE_SIZE);
			e->y = min(max(e->y, 0), MAP_HEIGHT * TILE_SIZE);
		}
		else if (e->flags & EF_LIGHT && (portalX == e->i[L_PARENT_X] && portalY == e->i[L_PARENT_Y])) {
			e->draw = 1;
			e->n = 5;
		}
	}
}

static void move(Entity *e) {
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

static void push(Entity *e, float dx, float dy) {
	moveToWorld(e, dx, dy);
	moveToEntities(e, dx, dy);
}

static int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return (max(x1, x2) < min(x1 + w1, x2 + w2)) && (max(y1, y2) < min(y1 + h1, y2 + h2));
}

static void moveToWorld(Entity *e, float dx, float dy) {
	int mx, my, hit, adj;

	if (dx != 0) {
		mx = dx > 0 ? (int)(e->x + e->w) : (int)e->x;
		mx /= TILE_SIZE;

		my = (int)(e->y / TILE_SIZE);

		hit = 0;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
			hit = 1;
		}

		my = (int)(e->y + e->h - 1) / TILE_SIZE;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
			hit = 1;
		}

		if (hit) {
			adj = dx > 0 ? -e->w : TILE_SIZE;

			e->x = (float)((mx * TILE_SIZE) + adj);

			e->dx = 0;
		}
	}

	if (dy != 0) {
		my = dy > 0 ? (int)(e->y + e->h) : (int)e->y;
		my /= TILE_SIZE;

		mx = (int)e->x / TILE_SIZE;

		hit = 0;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
			hit = 1;
		}

		mx = (int)(e->x + e->w - 1) / TILE_SIZE;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
			hit = 1;
		}

		if (hit) {
			adj = dy > 0 ? -e->h : TILE_SIZE;

			e->y = (float)((my * TILE_SIZE) + adj);

			e->dy = 0;

			e->isOnGround = dy > 0;
		}
	}
}

static void moveToEntities(Entity *e, float dx, float dy) {
	Entity *other;
	int adj;

	for (other = stage.entityHead.next; other != NULL; other = other->next) {
		if (other != e && collision((int)e->x, (int)e->y, e->w, e->h, (int)other->x, (int)other->y, other->w, other->h)) {

			if (other->flags & EF_PLATFORM) {
				if (dy != 0 && (int)((e->y - e->dy) + e->h) <= other->y) {
					adj = dy > 0 ? -e->h : other->h;

					e->y = other->y + adj;

					e->dy = 0;

					if (dy > 0) {
						e->isOnGround = 1;
						e->riding = other;
					}
				}
			}

			if (e->touch) {
				e->touch(other);
			}
		}
	}
}

void drawEntities(void) {
	Entity *e;
	for (e = stage.entityHead.next; e != NULL; e = e->next) {
		if (e->draw) blit(e->texture, (int)(e->x - stage.camera.x), (int)(e->y - stage.camera.y));
	}
}

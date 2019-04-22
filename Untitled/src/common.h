#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "ctype.h"

#include "SDL.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAX_TILES 4
#define TILE_SIZE 64

#define MAP_WIDTH 40
#define MAP_HEIGHT 12
#define MAP_RENDER_WIDTH 20
#define MAP_RENDER_HEIGHT 12

#define MAX_FILENAME_LENGTH 32
#define MAX_LINE_LENGTH 128
#define MAX_NAME_LENGTH 32

#define MAX_KEYBOARD_KEYS 350
#define CUR 0
#define RPT 1

#define MAX_SND_CHANNELS 16

#define EF_WEIGHTLESS (2 << 0)
#define EF_PLATFORM (2 << 1)
#define EF_ITEM (2 << 2)
#define EF_PORTAL (2 << 3)

enum {
	SND_ITEM,
	SND_JUMP,
	SND_PORTAL,
	SND_MAX
};

enum {
	CH_ITEM,
	CH_PLAYER,
	CH_PORTAL
};

typedef struct Texture Texture;
typedef struct Entity Entity;

typedef struct {
	void(*draw)(void);
	void(*logic)(void);
} Delegate;

struct Texture {
	char name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

typedef struct {
	int debug;
	int map;
	int keyboard[MAX_KEYBOARD_KEYS][2];
	Delegate delegate;
	SDL_Renderer *renderer;
	SDL_Window *window;
	Texture textureHead;
	Texture *textureTail;
} Game;

struct Entity {
	float x;
	float y;
	float ex;
	float ey;
	float sx;
	float sy;
	float dx;
	float dy;
	float n;
	int w;
	int h;
	int hp;
	int isOnGround;
	long flags;
	Entity *riding;
	Entity *next;
	SDL_Texture *texture;
	void(*tick)(void);
	void(*touch)(Entity *other);
};

typedef struct {
	int x;
	int y;
	int xTarget;
	int yTarget;
} Camera;

typedef struct {
	int map[MAP_WIDTH][MAP_HEIGHT];
	Camera camera;
	Entity entityHead;
	Entity *entityTail;
} Stage;

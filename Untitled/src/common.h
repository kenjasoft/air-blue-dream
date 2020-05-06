#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "ctype.h"
#include "time.h"

#include "SDL.h"
#include "SDL_ttf.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 768
#define CAMERA_OFFSET 19

#define MAP_WIDTH 384
#define MAP_HEIGHT 3840
#define PLAYER_WIDTH 60
#define PLAYER_HEIGHT 74

#define MAX_FILENAME_LENGTH 32
#define MAX_LINE_LENGTH 128
#define MAX_NAME_LENGTH 32
#define MAX_TEXTURES 34
#define MAX_LANDSCAPE 3
#define MAX_CLEAR_TEXT 6
#define LANDSCAPE_WIDTH 64
#define LANDSCAPE_HEIGHT 170
#define MAX_SKY 6
#define SKY_WIDTH 78
#define SKY_HEIGHT 60
#define MAX_CLOUDS 3
#define CLOUD1_WIDTH 96
#define CLOUD1_HEIGHT 28
#define CLOUD2_WIDTH 64
#define CLOUD2_HEIGHT 20

#define MAX_KEYBOARD_KEYS 6
#define CUR 0
#define RPT 1

#define MAX_SND_CHANNELS 16

#define EF_WEIGHTLESS (2 << 0)
#define EF_PLATFORM (2 << 1)
#define EF_PORTAL (2 << 2)
#define EF_LIGHT (2 << 3)
#define EF_PLAYER (2 << 4)
#define EF_GROUND (2 << 5)
#define EF_PIGEON (2 << 6)
#define EF_CROW (2 << 7)

enum {
	SND_JUMP,
	SND_PORTAL,
	SND_MAX
};

enum {
	CH_PLAYER,
	CH_PORTAL
};

enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ACTION,
	FLY
};

enum {
	L_X,
	L_Y,
	L_HEIGHT,
	L_PHASE,
	L_AMP,
	L_FREQ,
	L_SPEED,
	L_DIR,
	L_ANGLE,
	L_PARENT_X,
	L_PARENT_Y
};

enum {
	TX_PLAYERCROUCH,
	TX_PLAYERIDLE1,
	TX_PLAYERIDLE2,
	TX_PLAYERIDLE3,
	TX_PLAYERIDLE4,
	TX_PLAYERJUMP,
	TX_PLAYERWALK1,
	TX_PLAYERWALK2,
	TX_PLAYERWALK3,
	TX_PLAYERWALK4,
	TX_ROCKPLATFORM,
	TX_TREE,
	TX_GROUND,
	TX_SKY,
	TX_LANDSCAPE,
	TX_BUSH,
	TX_CLOUD1,
	TX_CLOUD2,
	TX_FLOWERS,
	TX_MAPLE,
	TX_GRASSPLATFORM,
	TX_SMALLROCKPLATFORM,
	TX_PIGEONWALK1,
	TX_PIGEONWALK2,
	TX_PIGEONWALK3,
	TX_PIGEONWALK4,
	TX_PIGEONWALK5,
	TX_PIGEONWALK6,
	TX_PIGEONWALK7,
	TX_PIGEONWALK8,
	TX_CROWFLOAT1,
	TX_CROWFLOAT2,
	TX_CROWFLOAT3,
	TX_CROWFLOAT4
};

enum {
	P_JUMP_COUNTER,
	P_JUMP_LIMIT,
	P_CAN_JUMP,
	P_ANIMATION_SPEED
};

enum {
	C_X_FACTOR_MAJOR,
	C_Y_FACTOR_MAJOR,
	C_X_FACTOR_MINOR,
	C_Y_FACTOR_MINOR
};

enum {
	C_X_SIN,
	C_Y_SIN
};

enum {
	HIT_OFF,
	HIT_ON,
	HIT_ALWAYS
};

enum {
	UPPER,
	LOWER
};

static const int levelTop[6] = { 1442, 1408, 1716, 906, 84, 78 };
static const float textPositions[4][2] = { {-615, 153}, {231, 231}, {-469, 299}, {-401, 367} };

SDL_Texture* textures[MAX_TEXTURES];

typedef struct {
	void(*draw)(void);
	void(*logic)(void);
} Delegate;

typedef struct {
	int debug;
	int freeze;
	int map;
	int keyboard[MAX_KEYBOARD_KEYS][2];
	Delegate delegate;
	SDL_Renderer* renderer;
	SDL_Window* window;
} Game;

typedef struct Entity Entity;
struct Entity {
	float x;
	float y;
	float dx;
	float dy;
	float scaleX;
	float scaleY;
	float f[4];
	int i[11];
	int n;
	int w;
	int h;
	int hp;
	int hit;
	int draw;
	int isOnGround;
	long flags;
	Entity* riding;
	Entity* next;
	SDL_RendererFlip flip;
	SDL_Texture* texture;
	void(*tick)(void);
	void(*touch)(Entity* other);
};

typedef struct BareEntity BareEntity;
struct BareEntity {
	float x;
	float y;
	float yTarget;
	int w;
	int h;
	float f;
	SDL_RendererFlip flip;
	SDL_Texture* texture;
};

typedef struct {
	int x;
	int y;
	int xTarget;
	int yTarget;
} Camera;

typedef struct {
	int stageNumber;
	int holdTextScreen;
	int showTextScreen;
	int endStage;
	int endCamera;
	int playerAlpha;
	int endTimer;
	int newRecord;
	Camera camera;
	Entity entityHead;
	Entity* entityTail;
	BareEntity* sky[MAX_SKY];
	BareEntity* clouds[MAX_CLOUDS];
	BareEntity* landscape[MAX_LANDSCAPE];
	BareEntity* clearText[MAX_CLEAR_TEXT];
} Stage;

#include "common.h"

extern void blit(SDL_Texture* texture, int x, int y, float scaleX, float scaleY, SDL_RendererFlip flip);
extern void doCamera(void);
extern void doEntities(void);
extern void doPlayer(void);
extern void drawEntities(void);
extern void initEntities(void);
extern int fadeTexture(SDL_Texture* texture, int alpha);
extern void stopMusic(int fadeOut);
extern void playSound(int id, int channel);
extern void stopSound(int channel, int fadeOut);

extern Entity* player;
extern Game game;
extern Stage stage;

static const int levelTop[MAX_LEVELS] = { 2816, 1442, 1408, 1716, 906, 84, 78 };
static const float textPositions[MAX_TEXT][TEXT_MAX] = { {-615, 153}, {227, 227}, {-469, 299}, {-401, 367}, {-469, 299}, {-401, 367} };

#include "common.h"

extern void blit(SDL_Texture* texture, int x, int y, float scaleX, float scaleY, SDL_RendererFlip flip);
extern void doCamera(void);
extern void doEntities(void);
extern void doPlayer(void);
extern void drawEntities(void);
extern void initEntities(void);
extern int fadeTexture(SDL_Texture* texture, int alpha);

extern Entity* player;
extern Game game;
extern Stage stage;

#include "common.h"

extern void blit(SDL_Texture* texture, int x, int y, float scaleX, float scaleY, SDL_RendererFlip flip);
extern void initPlatform(char* line);
extern void initPlayer(char* line);
extern void initPigeon(char* line);
extern void initCrow(char* line);
extern void initPortal(char* line);
extern char* readFile(const char* filename);

extern Entity* self;
extern Stage stage;
extern Game game;

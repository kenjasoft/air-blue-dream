#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y);
extern void initPlatform(char *line);
extern void initPortal(char *line);
extern void initPlayer(char *line);
extern int isInsideMap(int x, int y);
extern char *readFile(const char *filename);

extern Entity *self;
extern Stage stage;

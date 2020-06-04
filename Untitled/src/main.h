#include "common.h"

#include "SDL_image.h"

extern void capFrameRate(long* then, float* remainder);
extern void saveHighScores(void);
extern void doInput(void);
extern void initGame(void);
extern int initSDL(void);
extern void initStage(void);
extern void prepareScene(void);
extern void presentScene(void);

Game game;
Entity* player;
Entity* self;
Stage stage;

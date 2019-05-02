#include "common.h"

extern SDL_Texture *createLightParticle(SDL_Renderer* renderer, int radius, int red, int green, int blue, int dim);
extern int fadeTexture(SDL_Texture* texture, int alpha);

extern Entity *self;
extern Stage stage;
extern Game game;

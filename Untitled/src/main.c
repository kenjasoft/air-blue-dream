#include "main.h"

int main(int argc, char* argv[]) {
	long then = SDL_GetTicks();
	float remainder = 0;

	srand((unsigned int)time(NULL));
	memset(&game, 0, sizeof(Game));

	initSDL();

	atexit(cleanup);

	initGame();
	initStage();

	while (stage.runGame) {
		prepareScene();

		doInput();

		game.delegate.logic();
		game.delegate.draw();

		presentScene();
		capFrameRate(&then, &remainder);
	}

	SDL_Quit();
	return 0;
}

static void capFrameRate(long* then, float* remainder)
{
	long wait = (long)(16 + *remainder);
	*remainder -= (int)*remainder;

	long frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;
	if (wait < 1) wait = 1;

	SDL_Delay(wait);

	*remainder += 0.667f;
	*then = SDL_GetTicks();
}

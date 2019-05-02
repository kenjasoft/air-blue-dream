#include "main.h"

int main(int argc, char *argv[]) {
	srand((unsigned int)time(NULL));
	memset(&game, 0, sizeof(Game));

	initSDL();

	atexit(cleanup);

	initGame();

	initStage();

	while (1) {
		prepareScene();

		doInput();

		game.delegate.logic();
		game.delegate.draw();

		presentScene();
	}
	return 0;
}

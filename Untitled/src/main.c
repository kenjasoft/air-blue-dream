#include "main.h"

int main(int argc, char *argv[]) {
	memset(&game, 0, sizeof(Game));
	game.textureTail = &game.textureHead;

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

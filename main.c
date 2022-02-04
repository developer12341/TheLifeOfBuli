#include "game.h"

void main() {
	Board board;
	Character buli, bear;

	//init the game objects
	initGame(&board, &buli, &bear);


	//start the game loop
	mainLoop(&board, &buli, &bear);
}
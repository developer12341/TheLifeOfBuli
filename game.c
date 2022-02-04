#include "game.h"

static int playerMove(Board* board, Character* buli, int prevMove) {
	/// <summary>
	/// this function inputs from the player what their next move will be.
	/// if the input is 0 then the next move will be the last move the player made
	/// if this is the first input from the player and they enter 0 the programe
	/// will ask them again.
	/// </summary>
	/// <param name="prevMove">the last code move the player made</param>
	/// <returns>the current move the player made</returns>


	int nextMove = 0;

	//print the instaction for the player
	printf("0 - move in the direction of your last move\n");
	printf("1 - move right\n");
	printf("2 - move left\n");
	printf("3 - move up\n");
	printf("4 - move down\n");
	do {
		//ask them for the input.
		printf("please enter your next move:");
		scanf_s("%d", &nextMove);
		//if the nextMove is 0 the next move is the last move
		//on first time it is called prevMove is -1 so the program will stay in
		//the loop and ask the player again.
		if (nextMove == 0)
			nextMove = prevMove;
		//if the input is not a proper value then go throw the loop again.
	} while (nextMove <= 0 || nextMove > 4);


	//init the next position to the current position
	int newX = buli->pos.x;
	int newY = buli->pos.y;

	//change it.
	switch (nextMove)
	{
	case 1:
		newX += 1;
		break;
	case 2:
		newX -= 1;
		break;
	case 3:
		newY -= 1;
		break;
	case 4:
		newY += 1;
		break;
	}
	//if the new position is valid
	if (getIndex(board, newY, newX) != '*') {

		//if the next piece is a point
		//decrement the amount of points because buli ate it.
		if (getIndex(board, newY, newX) == '#')
			board->pointAmount--;

		//the index buli was on is now empty
		setIndex(board, buli->pos.y, buli->pos.x, ' ');

		//set buli to be in the new position
		buli->pos.x = newX;
		buli->pos.y = newY;

		//set the next position to be buli.
		setIndex(board, buli->pos.y, buli->pos.x, 'B');
	}
	//return the move made.
	return nextMove;
}

static int normlize_value(int value) {
	//inputs - a value 
	//output - his sign.
	//it normlizes a 1D vector - turns its length to 1;
	if (value < 0)
		return -1;
	return value != 0;
}

static char enemyMove(Board* board, Character* bear, Character* buli, char standingOn) {
	/// <summary>
	/// this function calculates the next position of the bear.
	/// </summary>
	/// <param name="standingOn">the piece the bear stood on</param>
	/// <returns>the piece the bear is standing on</returns>
	int newX = bear->pos.x;
	int newY = bear->pos.y;
	newX += normlize_value(buli->pos.x - bear->pos.x);
	newY += normlize_value(buli->pos.y - bear->pos.y);

	//if the bear can go to the next position.
	if (getIndex(board, newY, newX) != '*') {

		//set the current piece to the piece he stood on
		setIndex(board, bear->pos.y, bear->pos.x, standingOn);

		//change the current position
		bear->pos.x = newX;
		bear->pos.y = newY;

		//save the piece the bear will stand on
		standingOn = getIndex(board, newY, newX);

		//set the piece the bear is headed to to 'D'
		setIndex(board, newY, newX, 'D');
	}
	return standingOn; // return the piece the bear is currently standing on.
}

void initGame(Board* board, Character* buli, Character* bear) {
	//this function inits the board, buli and the bear
	//init board
	fillBoard(board);
	inputWalls(board);
	//init buli
	inputCharacter("buli", board, buli, 'B');
	//init bear
	inputCharacter("bear", board, bear, 'D');
}

static void showBoard(Board* board) {
	clearScrean();
	printBoard(board);
}


void mainLoop(Board* board, Character* buli, Character* bear) {
	/// <summary>
	/// this function is the main loop of the game.
	/// it is responsible for printing to the screen, 
	/// asking the player for input and moving the enemy
	/// every turn it chacks if the game ended and if it did it prints an appropriate message
	/// </summary>

	// this ifs are here for the eadg case that the board is rigged to fail.
	// if the bear is on top of buli then buli lost
	if (bear->pos.x == buli->pos.x && bear->pos.y == buli->pos.y) {
		printf("you lost, but don't give up, play the game agine!");
		return;
	}
	// if there are no points in the board than buli won
	if (board->pointAmount == 0) {
		printf("yay you won");
		return;
	}

	//making the first move.
	boolean endGame = false;

	//the bear doesn't eat the points he staps on like buli,
	//this is why i need to save the piece the bear stands on.
	char BearStandingOn = '#';
	int prevMove = -1; // this number represent the last move the player made.

	do {
		//the main game loop

		showBoard(board);

		// the player's move
		prevMove = playerMove(board, buli, prevMove);

		//after the player made his move the bear need to make his move
		BearStandingOn = enemyMove(board, bear, buli, BearStandingOn);

		//chacking if the game has ended.
		if (bear->pos.x == buli->pos.x && bear->pos.y == buli->pos.y)
			endGame = true;

		if (board->pointAmount == 0)
			endGame = true;

	} while (!endGame);


	showBoard(board);

	// if the bear is on top of buli then buli lost
	if (bear->pos.x == buli->pos.x && bear->pos.y == buli->pos.y)
		printf("you lost, but don't give up, play the game again!");

	// if there are no points in the board than buli won
	if (board->pointAmount == 0)
		printf("yay you won");
}
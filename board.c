#include <stdio.h>
#include "board.h"
//this functions define the ways the board will be changed.
//it is basicly the API that we can see the board throw.

void setIndex(Board* board, int row, int col, char value) {
	//this function set an index in the board
	board->pieces[row][col] = value;
}

char getIndex(Board* board, int row, int col) {
	//this function return what a piece is in the board.
	return board->pieces[row][col];
}


void clearScrean() {
	system("cls"); // clear the screen
}

void fillBoard(Board* board) {
	//this function fills the board with the starting values.
	//it should be called first.
	board->pointAmount = 0;

	//these two loops set side walls
	//it initalize the board to be this
	//******
	//*?2#?*
	//*?2#?*
	//*?s3?*
	//******
	//?2#? - garbage values.
	for (int col = 0; col < BufferdRowSize; col++)
	{
		setIndex(board, 0, col, '*');
		setIndex(board, BufferdRowSize - 1, col, '*');
	}
	for (int row = 1; row < BufferdRowSize - 1; row++)
	{
		setIndex(board, row, 0, '*');
		setIndex(board, row, BufferdRowSize - 1, '*');
	}

	//this loop set every other piece to be a point.
	//in the start everywhere is only points.
	for (int row = 1; row < BufferdRowSize - 1; row++)
	{
		for (int col = 1; col < BufferdRowSize - 1; col++)
		{
			board->pointAmount++;
			setIndex(board, row, col, '#');
		}
	}
}

void printBoard(Board* board) {
	//print the board.
	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < rowSize; col++)
		{
			printf("%c ", getIndex(board, row + 1, col + 1));
		}
		putchar('\n');
	}
}

void inputWalls(Board* board) {

	/// <summary>
	/// this function input a filled board such as
	/// ****
	/// *##*
	/// *##*
	/// ****
	/// and asks the player where they want to put extra walls
	/// my coordinate system is:
	/// y is up
	/// x is right
	/// _________x
	/// |
	/// |
	/// |
	/// y
	/// </summary>

	int x = 0, y = 0;

	clearScrean();

	do {
		if (getIndex(board, y, x) == '#') {
			//if the player picked a spot that doesnt have a wall 
			//we will put a wall there and decrement the number of points 
			board->pointAmount--;
			setIndex(board, y, x, '*');
		}
		printBoard(board);

		//asking the player for the coordinates
		printf("please enter the X index(1 - %d): ", rowSize);
		scanf_s("%d", &x);

		printf("please enter the Y index(1 - %d): ", rowSize);
		scanf_s("%d", &y);

		clearScrean();

	} while (x > 0 && x < BufferdRowSize - 1 && y > 0 && y < BufferdRowSize - 1);
	//if the player choose to pick an invalide position we should end the input.
}

void inputCharacter(char* Character_name, Board* board, Character* character,
	char BoardValue) {

	//this function inputs a character.
	clearScrean();
	printBoard(board);

	//printing a massage
	printf("please enter %s's strating place\n", Character_name);
	printf("%s cant be outside of the map or in one of the walls\n", Character_name);
	do {
		//it asks the player for a proper input
		printf("please enter the X index(1 - %d): ", rowSize);
		scanf_s("%d", &(character->pos.x));

		printf("please enter the Y index(1 - %d): ", rowSize);
		scanf_s("%d", &(character->pos.y));

		//if the player inputed an invalid position 
		//or a filled (a position that doesnt have a point)
		//we ask them again.
	} while (character->pos.x <= 0 || character->pos.x >= BufferdRowSize - 1 ||
		character->pos.y <= 0 || character->pos.y >= BufferdRowSize - 1 ||
		getIndex(board, character->pos.y, character->pos.x) != '#');

	//if the character is buli we should decrement the amount of points.
	if (BoardValue == 'B')
		board->pointAmount--;

	//set the index the the char representing the character
	setIndex(board, character->pos.y, character->pos.x, BoardValue);
}


#define rowSize 30
#define BufferdRowSize (rowSize + 2)

typedef struct {
	int pointAmount;
	char pieces[BufferdRowSize][BufferdRowSize];
} Board;

typedef struct { int x, y; } Point;
typedef struct { Point pos; } Character;

void setIndex(Board* board, int row, int col, char value);

char getIndex(Board* board, int row, int col);

void clearScrean();

void fillBoard(Board* board);

void printBoard(Board* board);

void inputWalls(Board* board);

void inputCharacter(char* Character_name, Board* board, Character* buli,
	char BoardValue);


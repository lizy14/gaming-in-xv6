#include "types.h"
#include "stat.h"
#include "user.h"
#define MAX_X 40
#define MAX_Y 24
#define MaxSize (1000 + 10)
#define true 1
#define false 0
#define chrSnake ((char)(219))
#define chrFood ((char)(176))
typedef enum{DOWN, UP, LEFT, RIGHT} Dir;
typedef enum{RUNNING, OVER, VICTORY, EXIT} GameStatus;
typedef int bool;
typedef struct
{
	int x;
	int y;
} Pos;

typedef struct
{
	Pos pos[MaxSize];
	Dir dir;
	int length;
	int head;
} Snake;

Pos food;
Snake snake;
// if the snake eat the food in this time
bool eaten = 0;
GameStatus gameStatus;

void main_thread();
Pos getRandomPos();
Pos getFoodPos();
bool isPosEqual(const Pos p1, const Pos p2);
bool inSnake(const Pos pos);
void init();
int game();
void gameRestart();
void gameOver();
void gameVictory();

// move the snake and eat the food.
void logic();

// draw the snake and food
void draw();

// Change a char to lowercase if c is uppercase
// Nothing will be done if c is lowercase or not a English letter.
char charLower(const char c);

int main()
{
	main_thread();
	set_console_parameters(0);
	exit();
	return 0;
}

void main_thread()
{
	init();
	// set_timer(game, 1000);
	set_console_parameters(1);
	while(gameStatus != EXIT)
	{
		if(gameStatus == OVER)
			gameOver();
		else if(gameStatus == VICTORY)
			gameVictory();
		else
		{
			char c = ' ';
			read(0, &c, 1);
			c = charLower(c);
			switch(c)
			{
				case 'w':
					snake.dir = UP;
					break;
				case 'a':
					snake.dir = LEFT;
					break;
				case 'd':
					snake.dir = RIGHT;
					break;
				case 's':
					snake.dir = DOWN;
					break;
				case 'e':
					gameStatus = EXIT;
				default:
					continue;
			}
			game();
		}
	}
}

Pos getRandomPos()
{
	Pos pos;
	pos.x = random(0, MAX_X);
	pos.y = random(0, MAX_Y);
	return pos;
}

Pos getFoodPos()
{
	Pos pos = getRandomPos();
	while(inSnake(pos)){
		pos = getRandomPos();
	}
	return pos;
	// Pos p;
	// int x, y;
	// for(x = 10; x < MAX_X; x ++)
	// 	for(y = 10; y < MAX_Y; y ++)
	// 	{
	// 		p.x = x;
	// 		p.y = y;
	// 		if(! inSnake(p))
	// 			return p;
	// 	}
	// p.x = -1;
	// p.y = -1;
	// return p;
}

bool isPosEqual(const Pos p1, const Pos p2)
{
	if(p1.x == p2.x && p1.y == p2.y)
		return true;
	return false;
}

bool inSnake(const Pos pos)
{
	int i;
	for(i = 0; i < snake.length; i ++)
	{
		int cur = (snake.head + MaxSize - i) % MaxSize;
		if(isPosEqual(snake.pos[cur], pos))
			return true;
	}
	return false;
}

void init()
{
	clear_screen();
	snake.dir = UP;
	snake.length = 1;
	snake.head = 0;
	snake.pos[0].x = MAX_X / 2;
	snake.pos[0].y = MAX_Y / 2;
	food = getFoodPos();
	gameStatus = RUNNING;
	
	int x = snake.pos[snake.head].x;
	int y = snake.pos[snake.head].y;
	write_at(2 * food.x, food.y, chrFood);
	write_at(2 * food.x + 1, food.y, chrFood);
	write_at(2 * x, y, chrSnake);	
	write_at(2 * x + 1, y, chrSnake);
	
}

int game()
{
	logic();
	draw();	
	
	return 0;
}

void gameRestart()
{
	char c = ' ';
	c = charLower(c);

	while(c != 'r' && c != 'e')
		read(0, &c, 1);
	if(c == 'r')
	{
		init();
	}
	else
		gameStatus = EXIT;
}

void gameOver()
{
	clear_screen();
	printf(1, "%s\n", 
		"Game over!\npress r to restart\npress e to exit\n");
	gameRestart();
}

void gameVictory()
{
	clear_screen();
	printf(1, "%s\n",
		"Vicotry!\npress r to restart\npress e to exit\n");
	gameRestart();
}

void logic()
{
	Pos newHeadPos = snake.pos[snake.head];
	switch(snake.dir)
	{
		case DOWN:
			newHeadPos.y ++;
			break;
		case UP:
			newHeadPos.y --;
			break;
		case RIGHT:
			newHeadPos.x ++;
			break;
		case LEFT:
			newHeadPos.x --;
			break;
		default:
			printf(1, "error");
	}

	// Game over?
	if(inSnake(newHeadPos)
		|| newHeadPos.x < 0 || newHeadPos.x >= MAX_X
		|| newHeadPos.y < 0 || newHeadPos.y >= MAX_Y
		)
	{
		gameStatus = OVER;
	}
	// move the snake to the new position.
	snake.head = (snake.head + 1) % MaxSize;
	snake.pos[snake.head] = newHeadPos;
	if(isPosEqual(newHeadPos, food))
	{
		eaten = 1;
		snake.length ++;
		food = getFoodPos();
		if(snake.length > MaxSize)
		{
			gameStatus = VICTORY;
		}
	}
	else
		eaten = 0;
}

void draw()
{
	if(gameStatus != RUNNING)
		return;
	int head = snake.head;
	write_at(2 * snake.pos[head].x, snake.pos[head].y, chrSnake);
	write_at(2 * snake.pos[head].x + 1, snake.pos[head].y, chrSnake);
	if(eaten == 0){
		int cur = (head + MaxSize - snake.length) % MaxSize;
		int x = snake.pos[cur].x;
		int y = snake.pos[cur].y;
		write_at(2 * x, y, ' ');
		write_at(2 * x + 1, y, ' ');
	}
	else
	{
		write_at(2 * food.x, food.y, chrFood);
		write_at(2 * food.x + 1, food.y, chrFood);
	}
}

char charLower(char c)
{
	if(c >= 'A' && c <= 'Z')
		return(c - 'A' + 'a');
	return c;
}
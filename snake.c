#include "user.h"
#include "stat.h"
#include "user.h"
#define MAX_X 40
#define MAX_Y 25
#define MaxSize (1000 + 10)
typedef enum{DOWN, UP, LEFT, RIGHT} Dir;
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
bool eaten = 0;

// Pos getRandomPos();
Pos getFoodPos();
bool isPosEqual(const Pos p1, const Pos p2);
bool inSnake(const Pos pos);
void init();
int game();
void logic();
void draw();

int main()
{
	init();
	// set_timer(game, 1000);
	while(1)
	{
		char c = ' ';
		read(0, &c, 1);
		if(c >= 'A' && c <= 'Z')
			c = c - 'A' + 'a';
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
			default:
				break;
		}
		game();
	}
}

// Pos getRandomPos()
// {
// 	Pos pos;
// 	pos.x = rand(0, MAXX);
// 	pos.y = rand(0, MAXY);
// 	return pos;
// }

Pos getFoodPos()
{
	// Pos pos = getRandomPos();
	// while(inSnake(pos)){
	// 	pos = getRandomPos();
	// }
	for(int x = 0; x < MAX_X; x ++)
		for(int y = 0; y < MAX_Y; y ++)
		{
			Pos p;
			p.x = x;
			p.y = y;
			if(! inSnake(p))
				return p;
		}
}

bool isPosEqual(const Pos p1, const Pos p2)
{
	if(p1.x == p2.x && p1.y == p2.y)
		return true;
	else
		return false;
}

bool inSnake(const Pos pos)
{
	for(int i = 0; i < snake.length; i ++)
	{
		int cur = (head + i) % MaxSize;
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
	snake.pos[0].x = 20;
	snake.pos[0].y = 12;
	food = getFoodPos();
}

int game()
{
	logic();
	draw();
}

void logic()
{
	Pos newHeadPos = snake.pos[head];
	switch(snake.dir)
	{
		case DOWN:
			newHeadPos.y ++;
			beak;
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
			printf("error");
	}
	head = (head + 1) % MaxSize;
	snake.pos[head] = newHeadPos;
	if(isPosEqual(newHeadPos, food))
	{
		eaten = 1;
		snake.length ++;
		head = (head + 1) % MaxSize;
		snake.pos[head] = newHeadPos;
		food = getFoodPos();
	}
	else
		eaten = 0;
}

void draw()
{
	write_at(2 * snake.pos[head].x, snake.pos[head].y, 's');
	write_at(2 * snake.pos[head].x + 1, snake.pos[head].y, 's');
	if(eaten == 0){
		cur = head + MaxSize - length - 1;
		x = snake.pos[x];
		y = snake.pos[y];
		write_at(2 * x, y, ' ');
		write_at(2 * x + 1, y, ' ');
	}
	else
	{
		write_at(2 * food.x, food.y, 'f');
		write_at(2 * food.x + 1, food.y, 'f');
	}
}

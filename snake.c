#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

#define NUM_THREADS 2
#define TARGET_COUNT_PER_THREAD 50000
#define SEMAPHORE_NUM 0

uint g_counter;


//game logic

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
void draw_food();
void draw_snake_head();
void draw_length();
void draw_black_on_tail();

// Change a char to lowercase if c is uppercase
// Nothing will be done if c is lowercase or not a English letter.
char charLower(const char c);


void main_thread()
{
	init();
	set_console_parameters(CONS_NO_BUFFER | CONS_CDEFAULT);
	while(gameStatus != EXIT)
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
				break;
			default:
				continue;
		}
		game();
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

	draw_food();
	draw_snake_head();
	draw_length();
}

int game()
{
	if(gameStatus == OVER)
		gameOver();
	else if(gameStatus == VICTORY)
		gameVictory();
	else if(gameStatus == RUNNING)
	{
		logic();
		draw();
	}
	else
	{
		clear_screen();
		set_console_parameters(CONS_BUFFER | CONS_CDEFAULT);
		exit();
	}

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
	draw_snake_head();
	if(eaten == 0){
		draw_black_on_tail();
	}
	else
	{
		draw_food();
		draw_length();
	}
}

void draw_food()
{
	set_console_parameters(CONS_NO_BUFFER | CONS_CGREEN);
	write_at(2 * food.x, food.y, chrFood);
	write_at(2 * food.x + 1, food.y, chrFood);
	set_console_parameters(CONS_NO_BUFFER | CONS_CDEFAULT);
}

void draw_snake_head()
{
	set_console_parameters(CONS_NO_BUFFER | CONS_CBLUE);
	int x = snake.pos[snake.head].x;
	int y = snake.pos[snake.head].y;
	write_at(2 * x, y, chrSnake);
	write_at(2 * x + 1, y, chrSnake);
	set_console_parameters(CONS_NO_BUFFER | CONS_CDEFAULT);
}

void draw_length()
{
	set_console_parameters(CONS_NO_BUFFER | CONS_CRED);
	set_cursor(10, MAX_Y);
	printf(1, "Snake length: %d", snake.length);
	set_console_parameters(CONS_NO_BUFFER | CONS_CDEFAULT);
}

void draw_black_on_tail()
{
	int cur = (snake.head + MaxSize - snake.length) % MaxSize;
	int x = snake.pos[cur].x;
	int y = snake.pos[cur].y;
	write_at(2 * x, y, ' ');
	write_at(2 * x + 1, y, ' ');
}

char charLower(char c)
{
	if(c >= 'A' && c <= 'Z')
		return(c - 'A' + 'a');
	return c;
}












//multi-thread


void *thread(void *arg)
{
	sleep(10);
	int id = *(int*)arg;
	printf(1, "thread %d: started...\n", id);

	if(id==0)
		while(sleep(10),gameStatus!=EXIT)
			game();
	else{
		clear_screen();
		set_console_parameters(CONS_BUFFER | CONS_CDEFAULT);
		main_thread();
	}
	exit();
}

int main(int argc, char **argv)
{
	int i, j;

	int final_counter;
	int final_target = NUM_THREADS*TARGET_COUNT_PER_THREAD;


	// Initialize counter
	g_counter = 0;

	// Set up thread stuff

	// Stacks
	void *stacks[NUM_THREADS];
	// Args
	int *args[NUM_THREADS];

	// Allocate stacks and args and make sure we have them all
	// Bail if something fails
	for (i=0; i<NUM_THREADS; i++) {
		stacks[i] = (void*) malloc(4096);
		if (!stacks[i]) {
			printf(1, "main: could not get stack for thread %d, exiting...\n");
			exit();
		}

		args[i] = (int*) malloc(4);
		if (!args[i]) {
			printf(1, "main: could not get memory (for arg) for thread %d, exiting...\n");
			exit();
		}

		*args[i] = i;
	}

	printf(1, "main: running with %d threads...\n", NUM_THREADS);

	// Start all children
	for (i=0; i<NUM_THREADS; i++) {
		int pid = clone(thread, args[i], stacks[i]);
		printf(1, "main: created thread with pid %d\n", pid);
	}

	// Wait for all children
	for (i=0; i<NUM_THREADS; i++) {
		void *joinstack;
		join(&joinstack);
		for (j=0; j<NUM_THREADS; j++) {
			if (joinstack == stacks[i]) {
				printf(1, "main: thread %d joined...\n", i);
				break;
			}
		}

	}

	// Check the result
	final_counter = g_counter;
	printf(1, "Final counter is %d, target is %d\n", final_counter, final_target);
	if (final_counter == final_target)
		printf(1, "TEST PASSED!\n");
	else
		printf(1, "TEST FAILED!\n");


	// Exit
	exit();
}

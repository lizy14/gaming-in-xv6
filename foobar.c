#include "types.h"
#include "stat.h"
#include "user.h"
#define MAX_HEIGHT 24
#define MAX_WIDTH 80
int x=5, y=5;
int draw_method_flag = 0;

int draw(){
	if(draw_method_flag){
		clear_screen();
		write_at(x,y,'x');
	}else{
		int i;
		for(i=0; i<y; i++)
			printf(1,"\n");
		for(i=0; i<x; i++)
			printf(1," ");
		printf(1,"x");
		for(i=y;i<MAX_HEIGHT;i++)
			printf(1,"\n");
	}
	return 0;
}
int
main(int argc, char *argv[])
{
	if(argc>1)
		draw_method_flag = atoi(argv[1]);
	if(draw_method_flag){
		clear_screen();
		set_console_parameters(1);
	}
	printf(1,"%s\n","welcome to foobar! \npress w/a/s/d to move, e to quit.");
	while(1){
		char c;
		read(0,&c,1);
		int i=(int)c;
		switch(i){
		case 101://e
		  goto go_out;
	  case 97://a, left
		  x--; 
			break;
		case 115://s, down
			y++; 
			break;
		case 100://d,right
		  x++; 
			break;
		case 119://w, up
		  y--; 
			break;
		default:
		  continue;
		}
		x+=MAX_WIDTH;
		x%=MAX_WIDTH;
		y+=MAX_HEIGHT;
		y%=MAX_HEIGHT;
		draw();
	}
	go_out:
	if(draw_method_flag){
		set_console_parameters(0);
		clear_screen();
	}
	printf(1,"bye!\n");
	exit();
  return 0;
}

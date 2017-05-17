#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Line_Following.h"
#include "Server_Communication.h"
#include "Maze_Runner.h"
bool is_left();
bool is_right();
bool third_quadrant = false;
double m = 1;
int countright=0;
int countleft=0;
int reverse_count = 0;
int main(){ 

	init();
	int whiteThres = 100;
	int blackBinary = 0;
	int whiteBinary = 1;
	int PixelColours[32];
	int Parse = 0;
	int IRtestR = 0;
	int IRtestL = 0;
	int mazeThresh = 200;
	open_gate();
	while(1)
	{
	take_picture();
		IRtestL = IR_Check(0);
		IRtestR = IR_Check(1);
		printf("Right %d,Left %d\n ", IRtestR,IRtestL);
	for (int i=0; i<32; i++){

		PixelColours[i] = get_pixel(120, i*10, 3);

		if (PixelColours[i] < whiteThres)
		{
			PixelColours[i] = blackBinary;
		}
		else
		{
			PixelColours[i] = whiteBinary;
		}
		printf(" %d", PixelColours[i]);
	}
	printf("\n");
	if (IRtestR > mazeThresh && IRtestL > mazeThresh)
		{
			maze();
		}
	Parse = checkPosition(PixelColours);
	if(third_quadrant == false){
		if(Parse == 999){
			reverse();
		}else if(Parse == 666){
			third_quadrant =true;
		}else {
			move(Parse);
		}
	}else {
		 if(Parse == 999 && is_left()==false && is_right() == true){
			sharp_turn(false);
			printf("left\n");
		}else if(Parse == 999 && is_right()==false && is_left() == true){
			sharp_turn(true);
			printf("right\n");
		}
		 else if(Parse == 999 && is_left()==true && is_right() ==true){
            sharp_turn(true);
            printf("both\n");
              
			}else if (Parse == 999 && reverse_count > 9){
				do_180();
				reverse_count=0;
			}
        else if (Parse == 999 && is_left()==false && is_right() ==false){
				reverse();
				reverse_count++;
				printf("reverse\n");
		}
		else{
			move(Parse);
		}
	}
}


	return 0;
}

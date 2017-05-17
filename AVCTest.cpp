#include <stdio.h>
#include <time.h>
#include "E101.h"

int checkPosition(int array[]);
void move(int Error);
void reverse();
bool is_left();
bool is_right();
void sharp_turn(bool left);
void do_180();
void maze();
int IR_Check(int analog);
void gate();
bool third_quadrant = false;
double m = 1;
int countright=0;
int countleft=0;
int reverse_count = 0;

int main()
{ 
	init();
	int whiteThres = 100;
	int PixelColours[32];
	//int RedPix[32];
	int Parse = 0;
	//int redcount;
	int IRtestL;
	int IRtestR;
	int mazeThresh = 200;
	while(1)
	{
		//gate();
		take_picture();
		IRtestL = IR_Check(0);
		IRtestR = IR_Check(1);
		printf("Right %d,Left %d\n ", IRtestR,IRtestL);
		//redcount = 0;
		//sleep1(0,20000);
		for (int i=0; i<32; i++)
		{
			PixelColours[i] = get_pixel(120, i*10, 3);
			//RedPix[i] = get_pixel(120,i*10, 0);
			if (PixelColours[i] < whiteThres)
			{
				PixelColours[i] = 0;
			}
			else
			{
				PixelColours[i] = 1;
			}
			//if (RedPix[i] > 200)
			//{
			//	RedPix[i] = 3;
			//}
			//else
			//{
			//	RedPix[i] = 0;
			//}
		}
		//for (int i = 0; i < 32; i++)
		//{
			//if (RedPix[i] == 3)
			//{
			//	redcount++;
			//}
		//}
		//printf("red = %d\n", redcount);
		if (IRtestR > mazeThresh && IRtestL > mazeThresh)
		{
			break;
		}
		Parse = checkPosition(PixelColours);
		if(third_quadrant == false){
			if(Parse == 999)
			{
				reverse();
			}
			else if(Parse == 666)
			{
				third_quadrant =true;
			}
			else
			{
				move(Parse);
			}
		}
		else
		{
			if(Parse == 999 && is_left()==false && is_right() == true)
			{
					sharp_turn(true);
				//printf("left\n");
			}
			else if(Parse == 999 && is_right()==false && is_left() == true)
			{
				sharp_turn(false);
				//printf("right\n");
			}
			else if(Parse == 999 && is_left()==true && is_right() ==true){
            			sharp_turn(true);
            			//printf("both\n");
			}
			else if (Parse == 999 && reverse_count > 9)
			{
				do_180();
				reverse_count=0;
			}
        		else if (Parse == 999 && is_left()==false && is_right() ==false)
			{
				reverse();
				reverse_count++;
				//printf("reverse\n");
			}
			else
			{
				move(Parse);
			}
		}
	}
	//edit
	printf("MAZE\n");
	maze();
	//edit close
	return 0;
}

/** recevies an array and determines where the line is
* returns the 'weight' of position in relation to the line */
int checkPosition(int array[])
{
	int sum=0;
	int count=0;
	int countwhite=0;
	for(int i=0; i < 32; i++)
	{
		if(array[i] == 1)
		{
			sum = sum + (i-16.5)*5;
			countwhite++;
		}
		else
		{
			count++;
		}
	}
	if (count == 32)
	{
		return 999;
	}
	else if (countwhite == 32)
	{
		return 666;
	}
	else
	{
		return sum;
	}
}

/** recives error
* determines which direction correction is required
* scales error
*/
void move(int Error)
{
	int motor_speed = 0;
	//printf("Error = %d\n ", Error);
	if(Error > 0)
	{
		motor_speed =(int)((double)Error/800  + 160);
		set_motor(2, 220);
		set_motor(1,motor_speed);
		//printf("Motor Speed = %d\n ", motor_speed);
	}
	else if(Error < 0)
	{
		motor_speed = -(int)((double)Error/800  - 160);
		set_motor(2,motor_speed);
		set_motor(1,220);
		//printf("Motor Speed = %d\n ", motor_speed);
	}
	else
	{
		motor_speed = 150;
		set_motor(2,motor_speed);
		set_motor(1, motor_speed);
		//printf("Motor Speed = %d\n ", motor_speed);
	}
}

/** reverses for time when called*/
void reverse()
{
	set_motor(1, -200);
	set_motor(2, -200);
	sleep1(0, 75000);
	//printf("\n reverse");
}

/** Returns true if line is found to the left */
bool is_left()
{
	int countleft=0;
	int pixel_colours[16];
	int whiteThres = 100;
	for (int i=0; i<16; i++)
	{
		pixel_colours[i] = get_pixel(i*5 + 50, 10, 3);
		if (pixel_colours[i] > whiteThres)
		{
			countleft++;
		}
	}
	//printf("left count = %d\n", count);
	if (countleft > 3)
	{
		//printf("left\n");
		return true;
	}
	else
	{
		return false;
	}
}

/** Returns true if line is found to the right */
bool is_right()
{
	int countright=0;
	int pixel_colours[16];
	int whiteThres = 100;
	for (int i=0; i<16; i++)
	{
		pixel_colours[i] = get_pixel(i*5 +50, 310, 3);
		if (pixel_colours[i] > whiteThres)
		{
			countright++;
		}
	}
	//printf("right count = %d\n", count);
	if (countright > 3)
	{
		//printf("right\n");
		return true;
	}
	else
	{
		return false;
	}
}

/** recives bool input
* turns 90 degrees left if true */
void sharp_turn(bool left)
{
	if(left == true)
	{
		sleep1(0, 300000);
		set_motor(1, 180);
		set_motor(2, -180);
		sleep1(0, 300000);
	}
	else
	{
		sleep1(0, 300000);
		set_motor(2, 180);
		set_motor(1, -180);
		sleep1(0, 300000);
	}
}

/** Does a 180 degree turn when called */
void do_180()
{
	set_motor(1, 190);
        set_motor(2, -190);
        sleep1(0, 800000);
}

//edit
/** Determines actions made in the maze based on IR readings. */
void maze()
{
	int IRS_L;
	int IRS_R;
	int IRS_F;
	int wallThresleft = 350;
	int wallThresright = 500;
	int moveForward = 300;
	int objectThres = 600;
	//int reversecount = 0;
	while(1)
	{
		IRS_L = IR_Check(0);
		IRS_R = IR_Check(1);
		IRS_F = IR_Check(2);
		//sleep1(0,20000);
		printf("Left = %d, Right = %d, Front = %d \n", IRS_L, IRS_R, IRS_F);
		if(IRS_R > wallThresleft){
			move(-1600);
		}else if(IRS_R < wallThresright){
			move(1600);
		}else if(IRS_F > moveForward && IRS_R > wallThresleft){
			sharp_turn(false);
			move(0);
			sleep1(0, 50000);
			
		}else if (IRS_F > moveForward && IRS_R > wallThresright){
			sharp_turn(true);
			move(0);
			sleep1(0, 50000);
		}
}
}

/** takes IR reading and averages them
* call IR readings via ir.(L/R/F) */
int IR_Check(int analog)
{
	int IR = 0; //analog 0 is left, 1 is right, 2 is front
	/** checking average readings to account for noise */
	for(int i = 0; i < 5; i++)
	{
		IR = IR+read_analog(analog);
	}
	IR = IR/5;
	return IR;
}

/** Opens the gate */
void gate()
{

}





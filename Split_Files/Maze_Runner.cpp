#include "Maze_Runner.h"
void maze();

void maze()
{
	int IRS_L;
	int IRS_R;
	int IRS_F;
	int wallThres = 300;
	int moveForward = 400;
	int reverseThres = 600;
	int reversecount = 0;
	while(1)
	{
		IRS_L = IR_Check(0);
		IRS_R = IR_Check(1);
		IRS_F = IR_Check(2);
		//sleep1(0,20000);
		//printf("Left = %d, Right = %d, Frount = %d", IRS_L, IRS_R, IRS_F);
		if (IRS_L > IRS_R && IRS_F < moveForward)
		{
			move(800);
			printf("right");
		}
		else if (IRS_R > IRS_L && IRS_F < moveForward)
		{
			move(-800);
			printf("left");
		}
		else if (IRS_L == IRS_R && IRS_F < moveForward)
		{
			move(0);
		}
		else if (IRS_F > moveForward && IRS_L < wallThres)
		{
			sharp_turn(false);
		}
		else if (IRS_F > moveForward && IRS_R < wallThres)
		{
			sharp_turn(true);
		}
		if (IRS_F > reverseThres ||IRS_L > reverseThres || IRS_R > reverseThres )
		{
		if (reversecount < 10)
			{
				reverse();
				sleep1(0,200000);
			reversecount++;
			}
			else
			{
				sharp_turn(true);
				reversecount = 0;
			}
		}
	}
	while (1) //does doughnuts
	{
		sharp_turn(true);
	}
}


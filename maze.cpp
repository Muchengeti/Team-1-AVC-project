#include <stdio.h>
#include "E101.h"
#include <time.h>
#include "maze.h"
void move(int Error);
void reverse();
void sharp_turn(bool left);
int IR_Check(int analog);
void maze();
int reverse_count = 0;
int main(){
	
	return 0;
}
void sharp_turn(bool left){
	if(left == true){
		sleep1(0, 350000);
		set_motor(1, 160);
		set_motor(2, -160);
		sleep1(0, 400000);
	}else{
		sleep1(0, 350000);
		set_motor(2, 160);
		set_motor(1, -160);
		sleep1(0, 400000);
	}
}

void reverse(){
	set_motor(1, -200);
	set_motor(2, -200);
	sleep1(0, 75000);
	printf("\n reverse");
}
void move(int Error){
	int motor_speed =0; 
	//printf("Error = %d\n ", Error); 

	if(Error > 0) {
		motor_speed =(int)((double)Error/800  + 150);
		set_motor(2, 220);
		set_motor(1,motor_speed);
		//printf("Motor Speed = %d\n ", motor_speed);
	}else if(Error < 0) {
		motor_speed = -(int)((double)Error/800  - 150);
		set_motor(2,motor_speed);
		set_motor(1,220);
		//printf("Motor Speed = %d\n ", motor_speed);
	}

	else{
		motor_speed = 150;
		set_motor(2,motor_speed);
		set_motor(1, motor_speed);
		//printf("Motor Speed = %d\n ", motor_speed);
	} 


}
void maze()
{
	int IRS_L;
	int IRS_R;
	int IRS_F;
	int wallThres = 300;
	int moveForward = 400;
	while(1)
	{
		IRS_L = IR_Check(0);
		IRS_R = IR_Check(1);
		IRS_F = IR_Check(2);
		//sleep1(0,20000);
		printf("Left = %d, Right = %d, Frount = %d", IRS_L, IRS_R, IRS_F);
		if (IRS_L > IRS_R && IRS_F < moveForward)
		{
			move(-800);
		}
		else if (IRS_R > IRS_L && IRS_F < moveForward)
		{
			move(800);
		}
		else if (IRS_L == IRS_R && IRS_F < moveForward)
		{
			move(0);
		}
		else if (IRS_F >= moveForward && IRS_L > wallThres)
		{
			
			sharp_turn(false);
			
		}
		else if (IRS_F > moveForward && IRS_R > wallThres)
		{
			
			sharp_turn(true);
		}
		//if (IRS_F < objectThres)
		//{
		//	if (reversecount < 10)
		//	{
		//		reverse();
		//		sleep1(0,200000);
		//		reversecount++;
		//	}
		//	else
		//	{
		//		break;
		//	}
		//}
	}
	while (1) //does doughnuts
	{
		sharp_turn(true);
	}
}

/** takes IR reading and averages them
* call IR readings via ir.(L/R/F) */
int IR_Check(int analog)
{
	int IR = 0; //analog 0 is left, 1 is right, 2 is frount
	/** checking average readings to account for noise */
	for(int i = 0; i < 5; i++)
	{
		IR = IR+read_analog(analog);
	}
	IR = IR/5;
	return IR;
}

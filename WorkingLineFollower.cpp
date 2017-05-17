#include <stdio.h>
#include <time.h>
#include "E101.h"
int checkPosition(int array[]);
int move(int Error);
int reverse();
int degree90(int Error);
bool is_left();
bool is_right();
int sharp_turn(bool left);
bool third_quadrant = false;
double m = 1;
int countright=0;
int countleft=0;
int do_180();
int reverse_count = 0;
int IR_Check(int analog);
void maze();
int main(){ 

	init();
	int whiteThres = 100;
	int blackBinary = 0;
	int whiteBinary = 1;
	int PixelColours[32];
	int Parse = 0;
	int IRtestR = 0;
	int IRtestL = 0;
	int mazeThresh = 300;
	
	char addr[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(addr, 1024);
	char to_serv[24]={'P','l','e','a','s','e',0};
	send_to_serv(to_serv);
	char from_serv[19];
	receive_from_server(from_serv);
	for(int length = 0; length < 6; length++){
		to_serve[length] = from_serv[length];
	}
	send_to_serv(to_serve);
	sleep1(1,0); 
	while(1)
	{
	take_picture();
			IRtestL = IR_Check(0);
		IRtestR = IR_Check(1);
		printf("Right %d,Left %d\n ", IRtestR,IRtestL);
	//sleep1(0,20000);
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
			sharp_turn(true);
			printf("left\n");
		}else if(Parse == 999 && is_right()==false && is_left() == true){
			sharp_turn(false);
			printf("right\n");
		}
		 else if(Parse == 999 && is_left()==true && is_right() ==true){
            sharp_turn(false);
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

int checkPosition(int array[]){
	int sum=0;
	int count=0;
	int countwhite=0;
	for(int i=0; i < 32; i++){

		if(array[i] == 1){
			sum = sum + (i-16.5)*5;
			countwhite++;
		}
		else{
			count++;
		}

	}

	if (count == 32){
		return 999;
	}else if (countwhite == 32){
		return 666;
	}
	else {
		return sum;
	}
}
int move(int Error){
	int motor_speed =0; 
	//printf("Error = %d\n ", Error); 

	if(Error < 0) {
		motor_speed =(int)((double)Error/800  + 160);
		set_motor(2, 220);
		set_motor(1,motor_speed);
		//printf("Motor Speed = %d\n ", motor_speed);
	}else if(Error > 0) {
		motor_speed = -(int)((double)Error/800  - 160);
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

	return 0;
}
int reverse(){
	set_motor(1, -200);
	set_motor(2, -200);
	sleep1(0, 75000);
	printf("\n reverse");
	return 0;
}
bool is_left(){	
	int countleft=0;
	int pixel_colours[16];
	int whiteThres = 100;
	for (int i=0; i<16; i++){
		pixel_colours[i] = get_pixel(i*5 + 50, 10, 3);
		if (pixel_colours[i] > whiteThres)
		{
			countleft++;
		}
	}
//	printf("left count = %d\n", count);
	if (countleft > 3)
	{	//printf("left\n");
		return true;
	}else{
	return false;
	}
}
bool is_right(){
	int countright=0;
	int pixel_colours[16];
	int whiteThres = 100;
	for (int i=0; i<16; i++){
		pixel_colours[i] = get_pixel(i*5 +50, 310, 3);
		if (pixel_colours[i] > whiteThres)
		{
			countright++;
		}
	}
//	printf("right count = %d\n", count);
	if (countright > 3){
		//printf("right\n");
		return true;
	}else{
		return false;
	}
}
int sharp_turn(bool left){
	if(left == true){
		sleep1(0, 350000);
		set_motor(1, 180);
		set_motor(2, -180);
		sleep1(0, 400000);
	}else{
		sleep1(0, 350000);
		set_motor(2, 180);
		set_motor(1, -180);
		sleep1(0, 400000);
	}
	return 0;
}
int do_180(){
	set_motor(1, 190);
        set_motor(2, -190);
        sleep1(0, 800000);
	return 0;
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




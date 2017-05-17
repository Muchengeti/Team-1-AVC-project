#include "Standard_Commands.h"
int checkPosition(int array[]);
int move(int Error);
int reverse();
int degree90(int Error);
bool is_left();
bool is_right();
int sharp_turn(bool left);
int do_180();
int IR_Check(int analog);

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
	int pixel_colours[24];
	int whiteThres = 100;
	for (int i=0; i<24; i++){
		pixel_colours[i] = get_pixel(i*10, 10, 3);
		if (pixel_colours[i] > whiteThres)
		{
			countleft++;
		}
	}
//	printf("left count = %d\n", count);
	if (countleft > 3)
	{	printf("left\n");
		return true;
	}else{
	return false;
	}
}
bool is_right(){
	int countright=0;
	int pixel_colours[24];
	int whiteThres = 100;
	for (int i=0; i<24; i++){
		pixel_colours[i] = get_pixel(i*10, 310, 3);
		if (pixel_colours[i] > whiteThres)
		{
			countright++;
		}
	}
//	printf("right count = %d\n", count);
	if (countright > 3){
		printf("right\n");
		return true;
	}else{
		return false;
	}
}
int sharp_turn(bool left){
	if(left == true){
		sleep1(0, 200000);
		set_motor(1, 1);
		set_motor(2, -1);
		sleep1(0, 250000);
	}else{
		//sleep1(0,200000);
		set_motor(2, 1);
		set_motor(1, -1);
		sleep1(0, 25000);
	}
	return 0;
}
int do_180(){
	set_motor(1, 190);
        set_motor(2, -190);
        sleep1(0, 800000);
	return 0;
}
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

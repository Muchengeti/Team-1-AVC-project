#include <stdio.h>
#include <time.h>
#include "E101.h"

int checkPosition(int array[]);
int move(int Error);
int read_ir();
int reverse();
int degree90(int Error);
bool third_quadrant = false;

int main(){ 
	
	init();
	int whiteThres = 100;
	int blackBinary = 0;
	int whiteBinary = 1;
	int PixelColours[32];
	int Parse = 0;
	while(1)
	{
	take_picture();
	sleep1(0, 20000);
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
		
	}
	Parse = checkPosition(PixelColours);
	if(Parse == 999){
		reverse();
	}else if (Parse == 666 && third_quadrant == false)
	{
		third_quadrant =true;
	}
	}else if(third_quadrant == false){
		move(Parse);
	}else if(Parse == 666){
		degree90(Parse);
	}
	else{
		degree90(Parse);
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
	printf("Error = %d\n ", Error); 
	
	if(Error > 0) {
		motor_speed =(int)((double)Error/800 *50 + 150);
		set_motor(2,200);
		set_motor(1, (int)(motor_speed));
		printf("Motor Speed = %d\n ", motor_speed);
	}else if(Error < 0) {
		motor_speed = -(int)((double)Error/800 *50 - 150);
		set_motor(2,(int)motor_speed);
		set_motor(1,200);
		printf("Motor Speed = %d\n ", motor_speed);
	}

	else{
		motor_speed = 180;
		set_motor(2,(int)(motor_speed));
		set_motor(1, (int)(motor_speed));
		printf("Motor Speed = %d\n ", motor_speed);
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
int degree90(int Error) {
	int motor_speed;
	if(Error > 0) {
		motor_speed =(int)((double)Error/800 *50 + 150);
		set_motor(2,200);
		set_motor(1, (int)(motor_speed));
		printf("Motor Speed = %d\n ", motor_speed);
	}else if(Error < 0) {
		motor_speed = -(int)((double)Error/800 *50 - 150);
		set_motor(2,(int)motor_speed);
		set_motor(1,200);
		printf("Motor Speed = %d\n ", motor_speed);
	}else if (Error == 666) {
		set_motor(2,120);
		set_motor(1, 180);
	}

	else{
		motor_speed = 180;
		set_motor(2,(int)(motor_speed));
		set_motor(1, (int)(motor_speed));
		printf("Motor Speed = %d\n ", motor_speed);
	} 
	return 0;
}


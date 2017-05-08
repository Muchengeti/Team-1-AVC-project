#include "E101.h"
#include <stdio.h>
#include <time.h>

int getError(int[] array);
int reverse();
int move(int Error);
bool quadrant4 = false;
int main(){
	init();
	int white_binary = 1;
	int black_binary = 0;
	int threshold = 100;
	int parse_error = 0;
	int pixel_colour = 0;
	int[] pixel_array = int[32];
	while(1){
		take_picture();
		sleep1(0,50000);
		for(int i=0; i<32; i++){
			pixel_colour = get_pixel(120, i*10, 3);
			if(pixel_colour > threshold){
				pixel_array[i] = white_binary;
				
			}else{
				pixel_array[i] = black_binary;
			}
			
		}
		
	}
	parse_error = getError(pixel_array);
	if(parse_error == 999){
		reverse();
	}else if (parse_error == 888){
		if (quadrant4 == true){
			{
		move(parse_error);
			}else{
		quadrant4 == true;
			}	
	}else{
	{
		move(parse_error);
	}
	return 0;
}
int getError(int[] array){
	int error = 0;
	int count_black = 0;
	int count_white = 0;
	for(int i=0; i<32; i++){
		if (array[i] == 1){
			count_white++;
			error = error + (i-16.5)*5;
		}else{
			count_black++;
		}
	}
		if (count_black == 32){
			return 999;
		}else if (count_white == 32){
			return 888;
		}
		}else {
			return error;
		}
	
}
int move(int Error){
	int motor_speed = (int)((double)(Error / 800)) * 50 + 150;
	if (quadrant4 == true){
		if (Error == 888 || Error = 6*(16-16.5)*5){
			set_motor(1, 150);
			set_motor(2, 250);
			sleep1(0,50000);
			return 0;
		}
		else if(Error = -(6*(16-16.5)*5){
			
		set_motor(2, 150);
		set_motor(1, 250);
		sleep1(0,50000);
		return 0;
	}	
	
		if(Error > 0){
			set_motor(1, (int)(motor_speed/2);
			set_motor(2, motor_speed);
		}else if(Error < 0){
			set_motor(2, (int)(motor_speed/2);
			set_motor(1, motor_speed);
		}else{
			set_motor(1, 200);
			set_motor(2, 200);
		}

	
	return 0;
}
int reverse(){
	set_motor(1, -200);
	set_motor(2, -200);
	sleep(200000);
	printf("reverse\n");
	return 0;
}

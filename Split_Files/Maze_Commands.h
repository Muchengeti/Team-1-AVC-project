#ifndef C_MAZE_COMMANDS_H
#define C_MAZE_COMMANDS_H

#include "E101.h"
#include <time.h>
#include <stdio.h>
#include "Server_Communication.h"
#include "Line_Following.h"
#include "Maze_Runner.h"

int checkPosition(int array[]);
int move(int Error);
int reverse();
int degree90(int Error);
int sharp_turn(bool left);
int do_180();
int IR_Check(int analog);

#endif

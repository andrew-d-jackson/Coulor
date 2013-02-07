#include "easybmp/EasyBMP.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>

enum valueEnum {AVERAGE, RED, GREEN, BLUE, MIN, MAX};
enum directionEnum {UP, DOWN, LEFT, RIGHT};
enum nextActionEnum {NONE, MEMORYPOINTER, INCMEMORYPOINTER, DECMEMORYPOINTER, MEMORY, INCMEMORY,
	DECMEMORY, COPMEMORY, ADDMEMORY, MINMEMORY, PRINTN, PRINTC, IFEQUALV, IFEQUALM, IFLESSV, IFLESSM,
	IFGREATERV, IFGREATERM};

int valueRegisters[1024] = {0};
int memoryPointer = 0;

int currentPosX = 0;
int currentPosY = 0;

BMP image;

valueEnum valueType = RED;
directionEnum direction = RIGHT;
nextActionEnum nextAction = NONE;

int getValue(){
	RGBApixel pixel = image.GetPixel(currentPosX, currentPosY);

	if (valueType == AVERAGE)
		return ceilf(((int)pixel.Red + (int)pixel.Green + (int)pixel.Blue)/3);
	else if (valueType == MAX)
		if (((int)pixel.Red > (int)pixel.Green) && ((int)pixel.Red > (int)pixel.Blue))
			return (int)pixel.Red;
		else if (((int)pixel.Green > (int)pixel.Red) && ((int)pixel.Green > (int)pixel.Blue))
			return (int)pixel.Green;
		else
			return (int)pixel.Blue;
	else if (valueType == MIN)
		if (((int)pixel.Red < (int)pixel.Green) && ((int)pixel.Red < (int)pixel.Blue))
			return (int)pixel.Red;
		else if (((int)pixel.Green < (int)pixel.Red) && ((int)pixel.Green < (int)pixel.Blue))
			return (int)pixel.Green;
		else
			return (int)pixel.Blue;
	else if (valueType == RED)
		return (int)pixel.Red;
	else if (valueType == GREEN)
		return (int)pixel.Green;
	else
		return (int)pixel.Blue;
}

void move(){
	if (direction == UP)
		currentPosY--;
	else if (direction == DOWN)
		currentPosY++;
	else if (direction == LEFT)
		currentPosX--;
	else if (direction == RIGHT)
		currentPosX++;
}

void performActions(int action){
//Nothing
	if (action == 0){
		//Why is this here oh god

//Direction
	} else if (action == 10){
		direction = UP;
	} else if (action == 11){
		direction = DOWN;
	} else if (action == 12){
		direction = LEFT;
	} else if (action == 13){
		direction = RIGHT;

//Value Reading
	} else if (action == 20){
		valueType = RED;
	} else if (action == 21){
		valueType = GREEN;
	} else if (action == 22){
		valueType = BLUE;
	} else if (action == 23){
		valueType = AVERAGE;
	} else if (action == 24){
		valueType = MIN;
	} else if (action == 25){
		valueType = MAX;

//Memory Pointer
	} else if (action == 30){
		memoryPointer++;
	} else if (action == 31){
		memoryPointer--;
	} else if (action == 32){
		nextAction = MEMORYPOINTER;
	} else if (action == 33){
		memoryPointer = valueRegisters[memoryPointer];
	} else if (action == 34){
		nextAction = INCMEMORYPOINTER;
	} else if (action == 35){
		nextAction = DECMEMORYPOINTER;
	} else if (action == 36){
		memoryPointer += valueRegisters[memoryPointer];
	} else if (action == 37){
		memoryPointer -= valueRegisters[memoryPointer];

//Memory
	} else if (action == 40){
		nextAction = MEMORY;
	} else if (action == 41){
		valueRegisters[memoryPointer]++;
	} else if (action == 42){
		valueRegisters[memoryPointer]--;
	} else if (action == 43){
		nextAction = INCMEMORY;
	} else if (action == 44){
		nextAction = DECMEMORY;
	} else if (action == 45){
		nextAction = ADDMEMORY;
	} else if (action == 46){
		nextAction = MINMEMORY;
	} else if (action == 47){
		nextAction = COPMEMORY;

//Output
	} else if (action == 50){
		std::cout << (int)valueRegisters[memoryPointer];
	} else if (action == 51){
		std::cout << (char)valueRegisters[memoryPointer];
	} else if (action == 52){
		nextAction = PRINTN;
	} else if (action == 53){
		nextAction = PRINTC;

//Input
	} else if (action == 60){
		char* in;
		std::cin >> in;
		valueRegisters[memoryPointer] = (int)in[0];

//if
	} else if (action == 70){
		nextAction = IFEQUALV;
	} else if (action == 71){
		nextAction = IFEQUALM;
	} else if (action == 72){
		nextAction = IFLESSV;
	} else if (action == 73){
		nextAction = IFLESSM;
	} else if (action == 74){
		nextAction = IFGREATERV;
	} else if (action == 75){
		nextAction = IFGREATERM;

//System Tasks
	} else if (action == 200){
		exit(0);
	}

}

void performSpecialActions(int action){
	if (nextAction == MEMORYPOINTER){
		memoryPointer = action;
	} else if (nextAction == INCMEMORYPOINTER){
		valueRegisters[memoryPointer] += action;
	} else if (nextAction == DECMEMORYPOINTER){
		valueRegisters[memoryPointer] -= action;
	} else if (nextAction == MEMORY){
		valueRegisters[memoryPointer] = action;
	} else if (nextAction == INCMEMORY){
		valueRegisters[memoryPointer] += action;
	} else if (nextAction == DECMEMORY){
		valueRegisters[memoryPointer] -= action;
	} else if (nextAction == COPMEMORY){
		valueRegisters[action] = valueRegisters[memoryPointer];
	} else if (nextAction == ADDMEMORY){
		valueRegisters[memoryPointer] = valueRegisters[memoryPointer] + valueRegisters[action];
	} else if (nextAction == MINMEMORY){
		valueRegisters[memoryPointer] = valueRegisters[memoryPointer] - valueRegisters[action];
	} else if (nextAction == PRINTN){
		std::cout << action;
	} else if (nextAction == PRINTC){
		char tmp = action;
		std::cout << tmp;
	} else if (nextAction == IFEQUALV){
		if (valueRegisters[memoryPointer] == action)
			move();
	} else if (nextAction == IFEQUALM){
		if (valueRegisters[memoryPointer] == valueRegisters[action])
			move();
	} else if (nextAction == IFLESSV){
		if (valueRegisters[memoryPointer] < action)
			move();
	} else if (nextAction == IFLESSM){
		if (valueRegisters[memoryPointer] < valueRegisters[action])
			move();
	} else if (nextAction == IFGREATERV){
		if (valueRegisters[memoryPointer] > action)
			move();
	} else if (nextAction == IFGREATERM){
		if (valueRegisters[memoryPointer] > valueRegisters[action])
			move();
	}
}

int main(int argc, char* argv[]){
	//image.ReadFromFile("image.bmp");
	image.ReadFromFile(argv[1]);

	while(true){
		if (currentPosX < image.TellWidth() && currentPosY < image.TellHeight() && currentPosX >= 0 && currentPosY >= 0){
			if (nextAction == NONE){
				performActions(getValue());
				move();
			} else {
				performSpecialActions(getValue());
				nextAction = NONE;
				move();
			}
		} else {
			break;
		}
	} 
	return 0;
}

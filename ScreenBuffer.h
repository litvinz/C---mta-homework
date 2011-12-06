#pragma once
#include "gotoxy.h"
#include <iostream>

//this class is in charge of managing the bffer for the animation
// is creates buffer of screen size (+1) because screen size is from 0 to screen size so we need extra space
class ScreenBuffer
{
public:
	
	ScreenBuffer(void);
	
	//Helper function to check the buffer creation, prints it to screen (not being used in animation)
	void print(void);

	
	//static functions with screen size used for all the program to easly change screen size if required
	static const int screenWidth = 80;
	static const int screenHeight = 25;

	char buffer[screenWidth+1][screenHeight+1];
	//prints the differences between two given buffers to screen
	void printDiff(ScreenBuffer oldBuffer);
	~ScreenBuffer(void);
};


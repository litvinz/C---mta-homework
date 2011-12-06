#pragma once
#include "MyPoint.h"
#include "ScreenBuffer.h"
#include <iostream>
#include <windows.h>
#include <process.h>


/*
* a rectangle object
*/
class MyRectangle
{
	int width, height;
	MyPoint location;
	MyPoint direction;
	//private function for internal use
	void gotoxy(int, int);

public:
	MyRectangle(void);
	~MyRectangle(void);
	/*constrator for a new rectangle with the x,y,width,height attributes set*/
	MyRectangle (MyPoint,int,int);

	/*constrator for a new rectangle with the x,y,width,height and direction attributes set*/
	MyRectangle (MyPoint,int,int,MyPoint);

	//set a location for a specific rectangle (x, y)
	void setLocation(MyPoint pt);

	//set direction for a specific rectangle (x, y)
	void setDirection(MyPoint myDir);

	//set a size for a specific rectangle (width, height)
	void setSize (int width,int height);

	//prints a filled rectangle to the screen with the given char
	void DrawRetangle(char ch);

	//prints a filled rectangle to the screen with the given char
	void DrawRetangle(bool drawType ,char ch);	

	//moves the rectangle by addX, addY
	void move(int addX, int addY);
	
	//returns the position of the rectangle
	MyPoint getLocation();

	//Retruns movement for rectangle 
	MyPoint getDirection();

	//retruns rectangle height
	int getHeight();

	//retruns rectangle Width
	int getWidth();

	//Draws given rectangle to screen buffer
	ScreenBuffer DrawRetangleToBuffer(bool filled, ScreenBuffer *myBuffer);

	//compares 2 rectangles if they are alike by parameters
	bool islike(MyRectangle compare);
};
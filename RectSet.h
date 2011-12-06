#pragma once
#include "MyRectangle.h"
#include "ScreenBuffer.h"
#include <list>
#include <iostream>
#define DRAWING_FILLED   1
#define DRAWING_UNFILLED   0
using namespace std;
/*
* an ordered set of myRectangle objects
*/
class RectSet
{
	//function that detects if current rectangle exist in collition to any other rectangle and changes the direction accordingly
	//the collition is calculated inside the rect set
	void collisionDetection();

public:
	list<MyRectangle> lst;
	bool defaultDrawType;
	
	//copy contructor
	RectSet(const RectSet& mySet);
	RectSet(void);
	
	//find rectangle function from last to first
	list<MyRectangle>::iterator findIt(MyPoint rLocation);

	/*adds a rectangle to the top of the set*/
	void addRectangle(MyRectangle rect);
	
	/*deletes the given rectangle*/
	void deleteRect(MyRectangle *rect);

	/*puts the given rectangle on top of all the others*/
	void front(MyRectangle &myRect);

	/*puts the given rectangle behind of all the others*/
	void back(MyRectangle &myRect);

	/*finds a rectangle by its (x,y) coordinates*/
	MyRectangle* find(MyPoint rLocation);

	/*prints the whole set to the screen*/
	void drawAll();
	
	//draws to buffer the next step of transition animation
	ScreenBuffer drawToBuffer();


	/*sets the drawType (1-filled or 0-unfilled)*/
	void setDefaultDrawType(bool drawingType);
	
	/*sets the drawType (1-filled or 0-unfilled)*/
	bool getDefaultDrawType();

	//calculate next step for animation (adds direction to location)
	void nextStep(bool isTransition);

	//destructor
	~RectSet(void);
};



#pragma once
#include "RectSet.h"
#include "MyPoint.h"

//Only handles the rectangle menu (when option 4 is succesfull in finding one)
class RectMenu
{
	MyRectangle *rect;
	RectSet *mySet;
	bool checkDirInput(MyPoint point);
public:
	RectMenu(RectSet *rSet, MyRectangle *rect);
	~RectMenu(void);
	//Draws the menu to screen
	void drawMenu();
	
	//calls necessary function depending on user choise
	void handleMenu();
};


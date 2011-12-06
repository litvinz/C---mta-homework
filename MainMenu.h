#pragma once
#include "RectSet.h"
#include "RectMenu.h"
#include "RectSet.h"
#include "gotoxy.h"
#include "Menu.h"
#include "MyAnimation.h"
#include <iostream>
using namespace std;

class MainMenu
{
	RectSet mySet;
	void addRectMenu();
	void menuDrawRects();
	void menuChangeDrawType();
	void menuSelectRect();
public:
	MainMenu(RectSet &rectSet);
	~MainMenu(void);
	
	/*Prints the main menu to screen (dosen't handle the menu actions)*/
	void drawMenu();
	void handleMenu();
};


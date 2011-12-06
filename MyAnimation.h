#pragma once
#include "RectSet.h"
#include "ScreenBuffer.h"
#include "gotoxy.h"
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

//creates the animation based on 2 buffers
//this class only updates the screen given 2 buffers according to the selected animation type
class MyAnimation
{
public:
	void doAnimation(RectSet &mySet,bool isTransiction);
	MyAnimation(RectSet &mySet,bool isTransiction);
	MyAnimation(void);
	~MyAnimation(void);
};





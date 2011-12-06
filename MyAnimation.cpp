#include "MyAnimation.h"

//removed all includes from CPP file

MyAnimation::MyAnimation(void)
{
}


MyAnimation::MyAnimation(RectSet &mySet, bool isTransiction){
	RectSet aniSet(mySet);
	doAnimation(aniSet, isTransiction);
}




MyAnimation::~MyAnimation(void)
{
}

void MyAnimation::doAnimation(RectSet &mySet, bool isTransition){
       const int ESC = 27;
       clearScreen();
       ScreenBuffer *buffer1 = new ScreenBuffer(mySet.drawToBuffer());
       ScreenBuffer *buffer2 = new ScreenBuffer();
       ScreenBuffer *tmpBuffer = NULL;
       while (!(_kbhit() && (_getch() == ESC))){
		   mySet.nextStep(isTransition);
		   *buffer1 = mySet.drawToBuffer();
           buffer1->printDiff(*buffer2);
           tmpBuffer = buffer2;
           buffer2 = buffer1;
           buffer1 = tmpBuffer;
           Sleep(20);
       }
	   free(buffer1);
	   free(buffer2);
}




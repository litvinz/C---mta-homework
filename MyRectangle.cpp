#include "MyRectangle.h"

using namespace std;

void MyRectangle::setLocation(MyPoint myPoint){
	location = myPoint;
}

void MyRectangle::setSize(int rWidth, int rHeight) {
	width = rWidth;
	height = rHeight;
}

void MyRectangle::setDirection(MyPoint myDir){
	direction = myDir;
}

MyRectangle:: MyRectangle(void){
	direction = MyPoint(0,0);
	location = MyPoint(0,0);
	width = 0;
	height = 0;
}

MyRectangle::MyRectangle (MyPoint rLocation, int rWidth, int rHeight) {
	direction = MyPoint(0,0);
	location = rLocation;
	width = rWidth;
	height = rHeight;
}



MyRectangle::MyRectangle (MyPoint rLocation, int rWidth, int rHeight, MyPoint rDirection) {
	direction = rDirection;
	location = rLocation;
	width = rWidth;
	height = rHeight;
}


MyPoint MyRectangle::getLocation(){
	return location;
}

MyPoint MyRectangle::getDirection(){
	return direction;
}


/*Draws this rectangle with the given ch, according to the given drawType (filled or unfilled)*/
void MyRectangle::DrawRetangle(bool filled, char ch) {
	for (int i=0; i < height; i++){
		for (int j=0; j < width; j++){
			if (location.getX()+j >= 0 && location.getY()+i >= 0 && location.getX()+j <= ScreenBuffer::screenWidth && location.getY()+i <= ScreenBuffer::screenHeight){ //print only if not out of screen
				gotoxy((int)location.getX()+j,(int)location.getY()+i);
				if (i == 0 || i == height-1 || j==0 || j == width-1){
					cout << ch; //draw only if border
				} else {
					if (filled)
						cout << " "; //if drawType is set to filled, print spaces to fill the rectangle
					else 
						gotoxy((int)location.getX()+j,(int)location.getY()+i);  //if drawType is set to unfilled, just go to the following x,y
				}
			}		
		}
	}
}

/*Draws this rectangle with the given ch, as filled*/
void MyRectangle::DrawRetangle(char ch){
	DrawRetangle(true,ch);
}

/*move the rectangle*/
void MyRectangle::move(int addX, int addY){
	location.setX(location.getX() + addX);
	location.setY(location.getY() + addY);
}

/*assist function to go to a specific x,y coordinates on the screen*/
void MyRectangle::gotoxy(int scrX, int scrY)
	{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = scrX;
	dwCursorPosition.Y = scrY;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

int MyRectangle::getHeight(){
	return (int)height;
}

int MyRectangle::getWidth(){
	return (int)width;
}

ScreenBuffer MyRectangle::DrawRetangleToBuffer(bool filled, ScreenBuffer *myBuffer){
	int currX,currY;
	for (int i=0; i < height; i++){
		for (int j=0; j < width; j++){
			currX = (int)location.getX()+j;
			currY = (int)location.getY()+i;
			if ((currX > ScreenBuffer::screenWidth) && (currX < ScreenBuffer::screenWidth+ width +1))
				currX = currX - ScreenBuffer::screenWidth- 1;
			if (currY > ScreenBuffer::screenHeight && (currY < ScreenBuffer::screenHeight+height+1))
				currY = currY - ScreenBuffer::screenHeight - 1;
			if (currX >= 0 && currY >= 0 && currX <= ScreenBuffer::screenWidth && currY <= ScreenBuffer::screenHeight){ //print only if not TOTALLY out of screen
				if (i == 0 || i == height-1 || j==0 || j == width-1){
					myBuffer->buffer[currX][currY] = '*'; //draw only if border
				} else {
					if (filled)
						myBuffer->buffer[currX][currY] = ' '; //if drawType is set to filled, print spaces to fill the rectangle
				}
			}		
		}
	}
	return (*myBuffer);
}

bool MyRectangle::islike(MyRectangle compare){
	if ((location.getX() == compare.location.getX()) && (location.getY() == compare.location.getY()) && (height == compare.getHeight()) && (width == compare.getWidth())) return true;
	return false;
}


MyRectangle::~MyRectangle(void)
{
}
#include "MyPoint.h"


MyPoint::MyPoint(void)
{
	X = 0;
	Y = 0;
}

MyPoint::MyPoint(float myX, float myY)
{
	X = myX;
	Y = myY;
}


MyPoint::~MyPoint(void)
{
}


MyPoint::MyPoint(MyPoint left, MyPoint right)
{
	setX(left.getX()+right.getX());
	setY(left.getY()+right.getY());
}



float MyPoint::getX(void)
{
	return X;
}


float MyPoint::getY(void)
{
	return Y;
}


void MyPoint::setX(float myX)
{
	X = myX;
}


void MyPoint::setY(float myY)
{
	Y = myY;
}

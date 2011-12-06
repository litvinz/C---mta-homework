#pragma once
//handles x,y point modified to float for animation excersise
class MyPoint
{
public:

	MyPoint(void);
	MyPoint(float myX, float myY);
	~MyPoint(void);
	float getX(void);
	float getY(void);
	void setX(float myX);
	void setY(float myY);
	MyPoint::MyPoint(MyPoint left, MyPoint right);
private:
	float X;
	float Y;
};


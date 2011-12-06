#include "RectSet.h"
using namespace std;

RectSet::RectSet(void)
{
	defaultDrawType = DRAWING_FILLED;
}


RectSet::~RectSet(void)
{
}


//copy constructor
RectSet::RectSet(const RectSet& mySet){
	lst.assign(mySet.lst.begin(),mySet.lst.end());
	defaultDrawType = mySet.defaultDrawType;
}

void RectSet::addRectangle(MyRectangle rect){
	lst.push_back(rect);
}

void RectSet::deleteRect(MyRectangle *rect){
	lst.erase(findIt(rect->getLocation()));
}

void RectSet::front(MyRectangle &myRect){
	list<MyRectangle>::iterator it;
	it = findIt(myRect.getLocation());
	lst.splice(lst.end(),lst,it);
}

void RectSet::back(MyRectangle &myRect){
	list<MyRectangle>::iterator it;
	it = findIt(myRect.getLocation());
	lst.splice(lst.begin(),lst,it);
}

MyRectangle* RectSet::find(MyPoint rLocation){
	list<MyRectangle>::iterator it;
	MyRectangle* rect = NULL;   
	it = findIt(rLocation);
	if (it != lst.end())
		rect = &(it._Mynode()->_Myval);
	return rect;
}

list<MyRectangle>::iterator RectSet::findIt(MyPoint rLocation){
	list<MyRectangle>::iterator it;
	MyRectangle* rect = NULL;
	bool found = false;
	for(it = lst.begin(); it != lst.end() && !found; ++it){
		//height and width search to find the rectangle that occupies the space
		if (((*it).getLocation().getX() <= rLocation.getX()) && (((*it).getLocation().getX() + (*it).getWidth()) >= rLocation.getX())&& ((*it).getLocation().getY() <= rLocation.getY()) && (((*it).getLocation().getY() + (*it).getHeight()) >= rLocation.getY())){
			found = true;
		}
	}
	if (found) it--;
	return it;
}

void RectSet::drawAll(){
	list<MyRectangle>::iterator i;
	for(i = lst.begin(); i != lst.end(); ++i){
		(*i).DrawRetangle(defaultDrawType,'*');
	}
}

void RectSet::setDefaultDrawType(bool drawingType){
	defaultDrawType = drawingType;
}

bool RectSet::getDefaultDrawType(){
	return defaultDrawType;
}

ScreenBuffer RectSet::drawToBuffer(){
	list<MyRectangle>::iterator i;
	ScreenBuffer myBuffer;
	for(i = lst.begin(); i != lst.end(); ++i){
		(*i).DrawRetangleToBuffer(defaultDrawType, &myBuffer);
	}
	return myBuffer;
}

//cacluates the next step of the animation
void RectSet::nextStep(bool isTransition){
	list<MyRectangle>::iterator i;
	for(i = lst.begin(); i != lst.end(); ++i){
		MyPoint tmp = MyPoint((*i).getLocation(),(*i).getDirection());
		if (isTransition){
			if ((tmp.getX() > ScreenBuffer::screenWidth)&&(tmp.getX() <= ScreenBuffer::screenWidth+(*i).getWidth())) tmp.setX(0);
			if ((tmp.getY() > ScreenBuffer::screenHeight)&&(tmp.getY() <= ScreenBuffer::screenHeight+(*i).getHeight())) tmp.setY(0);
			if ((tmp.getX() < 0)&& (tmp.getX() > 0-(*i).getWidth())) tmp.setX(ScreenBuffer::screenWidth);
			if ((tmp.getY() < 0)&& (tmp.getY() > 0-(*i).getHeight())) tmp.setY(ScreenBuffer::screenHeight);
		}
		(*i).setLocation(tmp);
	}
	if (!isTransition) collisionDetection();
}

//here for every rect i calculate if there is a clition with any other
//and just change the rect direction if there is any
//all based in the fact that no specialdrawing is required when collition occurs
void RectSet::collisionDetection(){
	
	list<MyRectangle>::iterator i;
	list<MyRectangle>::iterator j;
	for(j = lst.begin(); j != lst.end(); ++j){
	MyPoint mylocation = (*j).getLocation();
	int myLeft = (int)mylocation.getX();
	int myRight = (int)mylocation.getX()+(*j).getWidth()-1;
	int myTop = (int)mylocation.getY();
	int myBottom = (int)mylocation.getY()+(*j).getHeight()-1;
	MyPoint myDirection = (*j).getDirection();
	MyPoint nextMyLocation = MyPoint(mylocation, myDirection); //needed for special check
						//Need variables to check special case
						int nextMyLeft = (int)nextMyLocation.getX();
						int nextMyRight = (int)nextMyLocation.getX()+(*j).getWidth()-1;
						int nextMyTop = (int)nextMyLocation.getY();
						int nextMyBottom = (int)nextMyLocation.getY()+(*j).getHeight()-1;
	float xDirection = myDirection.getX();
	float yDirection = myDirection.getY();
	for(i = j; i != lst.end(); ++i){
		if ((*j).islike((*i))){
			//check collition with borders of screen
			// check collition on X axe (left or right)
			if (((myLeft == (-1)) || (myRight == (ScreenBuffer::screenWidth+1)))
			||((myRight == (-1)) || (myLeft == (ScreenBuffer::screenWidth+1)))){
				 xDirection *= (-1);
			}
			if (((myTop == (-1)) || (myBottom == (ScreenBuffer::screenHeight+1)))
			||((myBottom == (-1)) || (myTop == (ScreenBuffer::screenHeight+1)))){
				yDirection *= (-1);
			}
		}
		else {
			//check collition with other rectangles
			MyPoint otherlocation = (*i).getLocation();
			MyPoint otherDirection = (*i).getDirection();
			MyPoint nextOtherLocation = MyPoint(otherlocation, otherDirection); //needed for special check
			int otherLeft = (int)otherlocation.getX();
			int otherRight = (int)otherlocation.getX()+(*i).getWidth()-1;
			int otherTop = (int)otherlocation.getY();
			int otherBottom = (int)otherlocation.getY()+(*i).getHeight()-1;
			float otherxDirection = otherDirection.getX();
			float otheryDirection = otherDirection.getY();
						//Need variables to check special case
						int nextOtherLeft = (int)nextOtherLocation.getX();
						int nextOtherRight = (int)nextOtherLocation.getX()+(*i).getWidth()-1;
						int nextOtherTop = (int)nextOtherLocation.getY();
						int nextOtherBottom = (int)nextOtherLocation.getY()+(*i).getHeight()-1;
			
			// check for colition on X axe
			if ((otherLeft == myLeft)  //internal collision same side
				||(otherLeft == myRight) //collision from left
				||(otherRight == myRight) // internal collision right side
				||(otherRight == myLeft) // collision from right
				//these are for special case that in the next step the 2 rectangles would jump collision point and destroy the animation
				//for example in case that rect one is in (1,0) and rect2 is in (2,0) and next step they both swap the coordinates, avoiding collition detection
				||(((myRight - otherLeft)  == (-1))&& ((myRight - otherLeft )*(-1)== (nextMyRight - nextOtherLeft)))
				||(((myRight - otherRight) == 1)&& ((myRight - otherRight)*(-1)== (nextMyRight - nextOtherRight)))
				||(((myLeft - otherRight)  == 1)&& ((myLeft  - otherRight)*(-1)== (nextMyLeft - nextOtherRight)))
				||(((myLeft - otherLeft)   == (-1))&& ((myLeft  - otherLeft )*(-1)== (nextMyLeft - nextOtherLeft)))
				)
			{
					//If there is common X between the 2 rectangles check borders (exclude corners problematic thing corners)
					if( ((myTop <= otherTop) && (myBottom >= otherTop)) ||
						((myTop <= otherBottom) && (myBottom >= otherBottom)) ||
						((myTop >= otherTop) && (myBottom <= otherBottom))){					
								//if there is common border check speed of impact
								if (((xDirection > 0) && (otherDirection.getX() >= 0)) 
								|| ((xDirection < 0) && (otherDirection.getX() < 0))){
									//if both rectangles have the same X speed change the direction of the greatest one
									if (((xDirection > 0)&&(xDirection >= otherDirection.getX()))
									|| ((xDirection < 0)&&(xDirection <= otherDirection.getX()))) xDirection *= (-1);
									else otherxDirection *= (-1);
									} else {
										xDirection *= (-1);
										otherxDirection *= (-1);
										}
						}
				}
			//check for colition in axe Y
			if ((otherTop == myTop)
				||(otherTop == myBottom)
				||(otherBottom == myBottom)
				||(otherBottom == myTop)
				//these are for special case that in the next step the 2 rectangles would jump collision point and destroy the animation
				||(((myTop - otherBottom)  == 1)&& ((myTop - otherBottom )*(-1)== (nextMyTop - nextOtherBottom)))
				||(((myTop - otherTop) == (-1))&& ((myTop - otherTop)*(-1)== (nextMyTop - nextOtherTop)))
				||(((myBottom - otherTop)  == (-1))&& ((myBottom  - otherTop)*(-1)== (nextMyBottom - nextOtherTop)))
				||(((myBottom - otherBottom)   == 1)&& ((myBottom  - otherBottom )*(-1)== (nextMyBottom - nextOtherBottom)))
				)
			{
					//If there is common Y between the 2 rectangles check borders (exclude corners problematic thing corners)
					if( ((myLeft <= otherLeft) && (myRight >= otherLeft)) ||
						((myLeft <= otherRight) && (myRight >= otherRight)) ||
						((myLeft >= otherLeft) && (myRight <= otherRight))){
								//if there is common border check speed of impact
								if (((yDirection > 0) && (otherDirection.getY() >= 0)) 
								|| ((yDirection < 0) && (otherDirection.getY() < 0))){
									//if both rectangles have the same X speed change the direction of the greatest one
									if (((yDirection > 0)&&(yDirection >= otherDirection.getY()))
									|| ((yDirection < 0)&&(yDirection <= otherDirection.getY()))) yDirection *= (-1);
									else otheryDirection *= (-1);
								} else {
									yDirection *= (-1);
									otheryDirection *= (-1);
								}

						}
				}
			//inserts updated direction into second drawing
			otherDirection.setX(otherxDirection);
			otherDirection.setY(otheryDirection);
			(*i).setDirection(otherDirection);
			}
		//updates direction
		myDirection.setX(xDirection);
		myDirection.setY(yDirection);
		(*j).setDirection(myDirection);
		}
	}
}


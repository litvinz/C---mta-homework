#include "RectMenu.h"
#include "gotoxy.h"
#include <iostream>
#include "Menu.h"
using namespace std;


RectMenu::RectMenu(RectSet *rSet, MyRectangle *myRect)
{
	mySet = rSet;
	rect = myRect;
}


RectMenu::~RectMenu(void)
{
}

void RectMenu::drawMenu(){
	clearScreen(); //clear the screen

	setTextColor( 7);
	mySet->drawAll(); //print all rectangles
	rect->DrawRetangle(mySet->getDefaultDrawType(),'+'); //print the selected rectangle with + chars

	//print the menu
	char *options[6] = {"Back",
					"Delete",
					"Move to front",
					"Move to back",
					"Move Rect",
					"Add Animation"};
	Menu myMenu(options, 6, false);
	myMenu.drawMenu();
}

/*handles actions for the selected rectangle*/
void RectMenu::handleMenu(){
	int action = 0;
	float x,y;
	gotoxy(47, 23);
	setTextColor(0xf);
	cout << "Menu option: ";
	cin >> action;
	
	while (action != 1){ //if 1 - back to main menu
		if (action == 2){ //2 - Delete
			mySet->deleteRect(rect);
			action = 1;
		} else if (action == 3){ //3 - Move to Front
			mySet->front(*rect);	
		} else if (action == 4){ //4 - Move to back
			mySet->back(*rect);
		} else if (action == 5){ //5 - Move rect
			gotoxy(47, 22);
			cout << "Move By (x,y):               ";
			gotoxy(62, 22);
			cin >> x;
			gotoxy(66, 22);
			cin >> y;
			rect->move(x,y);

		} else if (action == 6){ //Add Animation
			gotoxy(47, 22);
			cout << "Animate By (x,y): ";
			gotoxy(65, 22);
			cin >> x;
			gotoxy(69, 22);
			cin >> y;
			while (checkDirInput(MyPoint(x, y)) == false){
				setTextColor(0xc);	
				gotoxy(47, 23);
				cout << "Invalid Value";
				cin.get(); cin.get();
				gotoxy(47, 23);
				setTextColor(0xf);
				cout << "Animate By (x,y): ";
				gotoxy(65, 22);
				cin >> x;
				gotoxy(69, 22);
				cin >> y;
			}
			rect->setDirection(MyPoint(x, y));
		}
		
		/*if stay on this menu - print msgs and display the menu again for selection*/
		if (action != 1){ 
			drawMenu();
			if (action > 6){ //if invalid selection - show msg
				setTextColor(0xc);	
				gotoxy(47, 22);
				cout << "Invalid Selection!";
			}
			if (action == 5){
				gotoxy(47, 22);
				setTextColor( 0xa);
				cout << "Rect moved to pos ("<<rect->getLocation().getX()<<","<<rect->getLocation().getY()<<")";
			}
			gotoxy(47, 23);
			setTextColor( 0xf);
			cout << "Menu option: ";
			cin >> action;
		}
	}
}

bool RectMenu::checkDirInput(MyPoint point){
	if ((point.getX() >= (-1)) && (point.getX() <= 1) && (point.getY() >= (-1)) && (point.getY() <= 1)) 
		return true;
	return false;
}
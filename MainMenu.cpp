#include "mainMenu.h"



MainMenu::MainMenu(RectSet &rectSet)
{
	mySet = rectSet;
}


MainMenu::~MainMenu(void)
{
}

/*Prints the main menu screen (dosen't handle the menu actions)*/
void MainMenu::drawMenu(){
	clearScreen();
	setTextColor(7);
	mySet.drawAll(); 

	char* options[6] = {"Add Rect",
						"Draw (unfilled)",
						"Change to filled drawing",
						"Select Rect",
						"Animate transitions",
						"Animate collison"};


	
	if (mySet.getDefaultDrawType() == DRAWING_FILLED){
		options[1] = "Draw (filled)";
	}
	if (mySet.getDefaultDrawType() == DRAWING_FILLED){
		options[2] = "Change to unfilled drawing";
	} 

	Menu myMenu(options, 6, true);
	myMenu.drawMenu();
}

void MainMenu::handleMenu(){
	int action = 0;
	gotoxy(47, 23);
	setTextColor(0xf);
	cout << "Menu option: ";
	cin >> action;
	while (action != 9){
		drawMenu();
		if (action == 1){ //addRect
			addRectMenu();
		} else if (action == 2){ //Draw
			menuDrawRects();
		} else if (action == 3){ //change drawing type
			menuChangeDrawType();
		} else if (action == 4){ //select rect
			menuSelectRect();
		} else if (action == 5){ //Animate Transitions
			MyAnimation animate(mySet, true);
			drawMenu();
		} else if (action == 6){ //Animate Collition
			MyAnimation animate(mySet, false);
			drawMenu();
		} else {
			setTextColor(0xc);
			gotoxy(47, 22);
			cout << "Invalid Selection!";
			action = 0;
		}
		gotoxy(47, 23);
		setTextColor(0xf);
		cout << "Menu option: ";
		cin >> action;
	}
	clearScreen();
	cout << "Goodbye!\n";
}

void MainMenu::addRectMenu(){
	int x,y;
	int width, height;
	gotoxy(47, 22);
	cout << "Plase enter rect cords: ";
	cin >> x;
	gotoxy(74, 22);
	cin >> y;
	drawMenu();
	gotoxy(47, 22);
	cout << "Plase enter rect Size: ";
	cin >> width;
	gotoxy(74, 22);
	cin >> height;
	mySet.addRectangle(MyRectangle(MyPoint((float)x,(float)y),width,height));
	drawMenu();
	gotoxy(47, 22);
	setTextColor(0xa);
	cout << "Rect Added (" << x << "," << y << "," << width << "," << height << ")";
}

void MainMenu::menuDrawRects(){
	clearScreen();
	mySet.drawAll();
	gotoxy(0,0);
	cin.get();cin.get();
	drawMenu();
}

void MainMenu::menuChangeDrawType(){	
	if (mySet.getDefaultDrawType() == DRAWING_FILLED){
		mySet.setDefaultDrawType(DRAWING_UNFILLED);
	} else {
		mySet.setDefaultDrawType(DRAWING_FILLED);		
	}
	drawMenu();
	gotoxy(47, 22);
	setTextColor(0xa);
	cout << "Drawing mode changed";
}

void MainMenu::menuSelectRect(){
	int x,y;
	MyRectangle* rect;
	gotoxy(47, 22);
	cout << "Plase enter rect cords: ";
	gotoxy(71, 22);
	cin >> x;
	gotoxy(74, 22);
	cin >> y;
	rect = mySet.find(MyPoint((float)x,(float)y));
	if (rect == NULL){
		drawMenu();
		gotoxy(x, y);
		cout << "@";
		gotoxy(47, 22);
		setTextColor( 0xc);
		gotoxy(47, 22);
		cout << "Rect not found!";
	} else {
		RectMenu rectMenu(&mySet, rect);
		rectMenu.drawMenu();
		gotoxy(x, y);
		cout << "@";
		rectMenu.handleMenu();
		rectMenu.~RectMenu();
		drawMenu();	
	}
}
#include "RectSet.h"
#include "MainMenu.h"

void main(){
	RectSet mySet;
	MainMenu mainMenu(mySet);
	mainMenu.drawMenu();
	mainMenu.handleMenu();
}


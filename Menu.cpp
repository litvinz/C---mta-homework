#include "Menu.h"

Menu::Menu(char* menuOptions[], int menuSize, bool menuShowQuit){
	options = menuOptions;
	size = menuSize;
	showQuit = menuShowQuit;
}

Menu::Menu(void){
	options = NULL;
	size = 0;
	showQuit = false;
}

void Menu::drawMenu(){
	int startSize = screenHeight - size;
	gotoxy(45, startSize - 4);
	setTextColor(0xe); 
	cout << "+--------------------------------+";
	for (int i=0; i <= size+3; i++){
		gotoxy(45, startSize - 3 + i);
		cout << "+                                +";
		gotoxy(47, startSize - 3 + i);
		if (i < size)
			cout << i+1 << ". " << options[i];
		if (i == size && showQuit)
			cout << "9. Quit";
	}
	gotoxy(45, screenHeight);
	cout << "+--------------------------------+";
	setTextColor(7);
}
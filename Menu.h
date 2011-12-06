#include <iostream>
#include "gotoxy.h"
#include <iostream>
using namespace std;
//handles dinamic drawing of menues according to available options

const int screenHeight = 25;

class Menu{
	int size;
	char** options;
	bool showQuit;
	public:
		Menu();
		Menu::Menu(const Menu&);
		Menu(char** options, int size, bool menuShowQuit);
		void drawMenu();
};
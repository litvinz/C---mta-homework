/*Prints the specific rect menu to screen (dosen't handle the menu actions)*/
#include "gotoxy.h"
#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;

void gotoxy(int scrX, int scrY){
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = scrX;
	dwCursorPosition.Y = scrY;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void clearScreen(){
	system("cls");
}

void setTextColor(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
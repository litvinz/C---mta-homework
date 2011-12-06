#include "ScreenBuffer.h"

using namespace std;

ScreenBuffer::ScreenBuffer(void)
{
	for (int i=0; i <= screenWidth; i++){
		for (int j=0; j <= screenHeight; j++){
			buffer[i][j] = ' ';
		}
	}
}


void ScreenBuffer::print(void){
	for (int j=0; j <= screenHeight; j++)
		for (int i=0; i <= screenWidth; i++){
		{
			gotoxy(i,j);
			cout << buffer[i][j];
		}
	} 
}

void ScreenBuffer::printDiff(ScreenBuffer oldBuffer){
	for (int i=0; i <= screenWidth; i++){
		for (int j=0; j <= screenHeight; j++){
			if (oldBuffer.buffer[i][j] != buffer[i][j]){
				gotoxy(i,j);
				cout << buffer[i][j];
			}
		}
	}
}

ScreenBuffer::~ScreenBuffer(void)
{
}

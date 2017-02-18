#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800
#define X 123
#define Y 123

void mouseSetup(INPUT *buffer){
	
	buffer->type = INPUT_MOUSE;
	buffer->mi.dx = (0 * (0xFFFF) / SCREEN_WIDTH);
	buffer->mi.dy = (0 * (0xFFFF) / SCREEN_HEIGHT);
	buffer->mi.mouseData = 0;
	buffer->mi.time = 0;
	buffer->mi.dwExtraInfo =0;
}

void mouseMoveAbsolute(INPUT *buffer, int x, int y){

	buffer->mi.dx = (0 * (0xFFFF) / SCREEN_WIDTH);
	buffer->mi.dy = (0 * (0xFFFF) / SCREEN_HEIGHT);
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_ABSOLUTE);

	SendInput(1, buffer, sizeof(INPUT));
}

void MouseClick(INPUT *buffer){

	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, buffer, sizeof(INPUT));

	Sleep(10);

	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, buffer, sizeof(INPUT));
}

/*int main(){

	//INPUT buffer[1];
	
	int x = (int) (65536 / SCREEN_WIDTH) * 200 - 1;
	int y = (int) (65536 / SCREEN_HEIGHT) * 600 - 1;

	int moveUp = (int) (65536 / SCREEN_WIDTH)  * -80 - 1;
	int moveDown = (int) (65536 / SCREEN_WIDTH)  * 80 - 1;


	
	
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x, y,0,0);
	

	mouse_event(MOUSEEVENTF_ABSOLUTE| MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_ABSOLUTE| MOUSEEVENTF_LEFTUP,0,0,0,0);
	mouse_event(MOUSEEVENTF_ABSOLUTE| MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_ABSOLUTE| MOUSEEVENTF_LEFTUP,0,0,0,0);

	mouse_event(MOUSEEVENTF_ABSOLUTE| MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
	//mouse_event(MOUSEEVENTF_ABSOLUTE| MOUSEEVENTF_RIGHTUP,0,0,0,0);
	//mouse_event(MOUSEEVENTF_ABSOLUTE| MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
	//mouse_event(MOUSEEVENTF_ABSOLUTE| MOUSEEVENTF_RIGHTUP,0,0,0,0);

	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL , 0, 0, moveUp, 0);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL , 0, 0, moveUp, 0);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL , 0, 0, moveUp, 0);

	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL , 0, 0, moveDown, 0);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL , 0, 0, moveDown, 0);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_WHEEL , 0, 0, moveDown, 0);



	getchar();

	 
	return 0;

}*/


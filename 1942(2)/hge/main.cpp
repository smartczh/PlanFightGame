#include"data.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	lo = new Logic();
	gui = new GUI(lo);
	if (gui->hge->System_Initiate())
	{
		init_data();
		gui->hge->System_Start();
	}
	delete lo;
	delete gui;
    return 0;
}




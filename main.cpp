#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include "GameObject.h"
#include "Utils.h"
#include "Screen.h"
#include "Player.h"

#include "time.h"

using namespace std;

int main()
{
	Player player{ 2, 2 };


	Screen screen(10, 10);


	
	int count = 0;
	


	screen.clear();
	screen.clearscene();
	screen.setLandmine('*');
	screen.setNumber();
	while (1)
	{
		screen.clearscene();

		
		screen.screencopy();

		screen.draw(player.getPos(), player.getShape());

		screen.renderScene();


		//screen.renderAnswer();
		player.processInput(screen);
		

	}
	
	return 0;
}
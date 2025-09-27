#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include "GameObject.h"
#include "Utils.h"
#include "Screen.h"
#include "Player.h"
#include "Enemy.h"
#include "InputSystem.h"



using namespace std;

int main()
{
	Screen screen(10, 10);
	InputSystem input;
	Player player{ 2, 4, screen, input };

	screen.clear();
	screen.clearscene();
	screen.setLandmine('*');
	screen.setNumber();

	while (1)
	{
		screen.clearscene();
		screen.screencopy();

		input.readEveryFrame();

		screen.draw(player.getPos(), player.getShape());

		screen.renderScene();

		player.update();
	}
	
	return 0;
}
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>

#include "GameObject.h"
#include "Screen.h"

class Screen;
class Player :
    public GameObject
{
public:
    Player(int x, int y) : GameObject('>', x, y) {}

	void processInput(Screen& screen)
	{
		char key;

		cin >> key;

		Borland::GotoXY(0, 21);
		//printf("key is %c %d\n", key, key);

		Position pos = getPos();

		switch (key) {
		case 'w':
			pos.y--;
			break;
		case 'a':
			pos.x--;
			break;
		case 's':
			pos.y++;
			break;
		case 'd':
			pos.x++;
			break;
		case 'f':
			
			screen.checkFlag(pos);
			screen.isFlag(pos);
			break;
		case 'm':
			screen.checkTrap(pos);
			screen.mapOpen(screen.pos2offset(pos.x, pos.y, N_LANDMINE));
			break;
		}

		setPos(pos);

		/*if (input.getMouseButtonDown(0)) {
			auto mousePos = input.getMousePosition();
			Borland::GotoXY(10, 0);
			printf("mouse position [%03d, %03d]\n", mousePos.x, mousePos.y);
		}*/

	}
};


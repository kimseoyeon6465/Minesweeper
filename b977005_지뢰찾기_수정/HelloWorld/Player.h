#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <conio.h>
#include "GameObject.h"

class Player :
    public GameObject
{

	auto processInput()
	{
		auto pos = getPos();
		if (input.getKeyDown(0x57)) {
			pos.y--;
		}
		else if (input.getKeyDown(0x41)) {
			pos.x--;
		}
		else if (input.getKeyDown(0x53)) {
			pos.y++;
		}
		else if (input.getKeyDown(0x44)) {
			pos.x++;
		}
		else if (input.getKeyDown(0x46)) {//F키 눌러서 깃발
			screen.checkFlag(pos);
			screen.isFlag(pos);
		}
		else if (input.getKeyDown(0x4D)) //M키 눌러서 맵 열기
		{
			screen.checkTrap(pos);
			screen.mapOpen(screen.pos2offset(pos.x, pos.y, N_LANDMINE));
		}
		else if (input.getMouseButtonDown(0))//왼쪽 마우스 버튼 클릭으로 플레이어(커서) 이동, 맵 열기
		{
			auto mousePos = input.getMousePosition();
			pos.x = mousePos.x;
			pos.y = mousePos.y;
			screen.checkTrap(pos);
			screen.mapOpen(screen.pos2offset(pos.x, pos.y, N_LANDMINE));
			printf("\nmouse position [%03d, %03d]\n", mousePos.x, mousePos.y);
		}
		else if (input.getMouseButtonDown(1))//오른쪽 마우스 버튼을 클릭하면 플레이어(커서) 이동, 깃발 꼽기
		{
			auto mousePos = input.getMousePosition();
			pos.x = mousePos.x;
			pos.y = mousePos.y;
			screen.checkFlag(pos);
			screen.isFlag(pos);
		}
		setPos(pos);
	}
	

public:
    Player(int x, int y, Screen& screen, InputSystem& input) 
		: GameObject('>', x, y, screen, input) 
	{}


	void update() override
	{
		processInput();
	}

	void draw() override
	{	
		GameObject::draw();
		screen.draw(getPos() + Position{0, -1}, 'P');
	}

	
};


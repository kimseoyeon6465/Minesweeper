#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <iostream>
#include "Utils.h"
#include "Screen.h"
#include "InputSystem.h"

using namespace std;



class GameObject
{
	Position pos;
	char* shape;
	Dimension dim;

protected:
	InputSystem& input;
	Screen& screen;

public:
	GameObject(char shape, int x, int y, Screen& screen, InputSystem& input)
		: pos(x, y), shape(nullptr), dim(1, 1), screen(screen), input(input)
	{
		this->shape = (char*)new char[dim.size() + 1];
		this->shape[0] = shape;
		this->shape[dim.size()] = '\0';
	}

	virtual ~GameObject() {
		delete[] shape;
	}

	auto getPos() const { return pos; }

	void setPos(const Position& pos) 
	{ 
		if (screen.checkValidPos(pos) == false) 
			return;
		this->pos.x = pos.x; this->pos.y = pos.y; 
	}

	auto getShape() const { return shape[0]; }

	virtual void draw()
	{
		screen.draw(pos, shape[0]);
	}


	virtual void update() {}	
	
};


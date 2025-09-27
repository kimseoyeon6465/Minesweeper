#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <conio.h>
#include "GameObject.h"
class Enemy :
    public GameObject
{

    auto walkRandomly()
    {
        static Position idx2inc[] = { {-1, -1}, { 0, -1}, {1, -1}, {-1,0}, {0, 0},
            {1, 0}, { -1, 1}, {0, 1}, {1, 1} };

        setPos( getPos() + idx2inc[ rand() % 9 ] ) ;
    }

    void processInput()
    {
        auto pos = getPos();
        if (input.getKey(VK_LEFT)) { // left arrow
            pos.x--;
        }
        else if (input.getKey(VK_RIGHT)) { // right arrow
            pos.x++;
        }
        else if (input.getKey(VK_UP)) { // up arrow
            pos.y--;
        }
        else if (input.getKey(VK_DOWN)) { // down arrow
            pos.y++;
        }

        
        setPos(pos);

    }

public:
    Enemy(int x, int y, Screen& screen, InputSystem& input) 
        : GameObject('*', x, y, screen, input) 
    {}

    void update() override {
        //walkRandomly();
        processInput();
    }

    void draw() override
    {
        GameObject::draw();
        
        screen.draw(getPos() + Position{ 0, -1 }, 'E');
    }
};


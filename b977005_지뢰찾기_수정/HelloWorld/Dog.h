#pragma once


#include "Pet.h"
class Dog :
    public Pet
{
    unsigned int durationRattling; // in seconds

public:

    Dog(string name, int age, unsigned durationRattling = 1) : Pet(name, age), durationRattling(durationRattling)
    {
        cout << "Dog constructor" << endl;
    }


    ~Dog() {
        cout << "Dog destructor" << endl;
    }

    void bark() { cout << "bark" << endl; }


    void sleep() { 
        cout << "rattling "; Pet::sleep();
    
    }

};


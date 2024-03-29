#pragma once
#include <iostream>
#include "Point.h"

using namespace std;

class Monster {
    private:
        char _symbol;
        string _name;
        int _HP;
        int _strenght;
        int _AC;
        Point _position;
        
    public:
        void print();
        Monster(char symbol, string name, int hp, int strenght, int ac);
        void takeDamage(int damage);
        Monster copyMonster(Point position);
        /*Getters*/
        int getStrenght() { return _strenght; }
        int getHP() { return _HP; }
        int getAC() { return _AC; }
        char getSymbol() { return _symbol; }
        string getName() { return _name; }
        Point getPosition() { return _position; }
        /* Setters */
        void setPosition(Point position) { _position = position; }
};      
    
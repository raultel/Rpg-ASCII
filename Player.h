#pragma once

#include "Inventory.h"
#include <list>


class Player {
    private:
        int _HP;
        int _strenght;
        int _AC;
        Point _position;
        int _gold;
        Inventory _inventory;

    public:
        Player(Point position);
        void walk(Point difference);
        void addItem(Item newItem);
        void addGold(int gold);
        void printInfo();
        void takeDamage(int damage);
        /*Getters*/
        Point getPosition() { return _position; }
        Inventory getInventory() { return _inventory; }
        int getStrenght() { return _strenght; }
        int getHP() { return _HP; }
        int getAC() { return _AC; }
        /*Setters*/
        void setPosition(Point p) { _position = p; }
};
#pragma once
#include "Item.h"
#include <ncurses.h>
#include <list>

class Inventory{
    private:
        list<Item> _items;
        int numberItems;
    public:
        void printInventory();
        void addItem(Item item);
        bool removeItem(string itemName);
        bool checkItem(string itemName);
        Item getItem(Point position);
};
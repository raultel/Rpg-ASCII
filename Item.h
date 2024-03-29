#pragma once
#include <iostream>
#include "Point.h"

using namespace std;
class Item{
    private:
        string _name;
        int _price;
        int _count;
        Point _position;
        /* Pode colocar os atributos no futuro ou fazer descendentes*/
    public:
        /* Constructors */
        Item(string name, int price, int count);
        Item(string name, int price, Point position);
        /* Getters */
        int getPrice() { return _price; }
        string getName() { return _name; }
        int getCount () { return _count; }
        Point getPosition() { return _position; }

        /*Setters*/
        bool setCount(int count);

        void operator=(Item item2);

        void addOne();
        bool removeOne();
        void print();
};
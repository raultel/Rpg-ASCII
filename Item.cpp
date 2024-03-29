#include "Item.h"

Item::Item(string name, int price, int count) {
    _count = count;
    _name = name;
    _price = price;
}


Item::Item(string name, int price, Point position) {
    _count = 1;
    _name = name;
    _price = price;
    _position = position;
}

void Item::addOne() {
    _count++;
}
bool Item::removeOne() {
    if (_count == 0) {
        return false;
    }
    _count--;
    return true;
}
bool Item::setCount(int count) {
    if (count < 0)
        return false;
    _count = count;
    return true;
}

void Item::print() {
    cout << _name << " x" << _count; 
    cout << " (" << _position.getY() << "," << _position.getX() << ")" << endl;

}

void Item::operator=(Item item2) {
    _name = item2.getName();
    _price = item2.getPrice();
    _position = item2.getPosition();
    _count = item2.getCount();
}
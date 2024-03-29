#include "Point.h"

Point::Point () {
    _x = 0;
    _y = 0;
}

Point::Point(int y, int x) {
    _x = x;
    _y = y;
}

void Point::setX(int newX) { 
    _x = newX; 
}
void Point::setY(int newY) { 
    _y = newY; 
}


Point Point::operator+(Point p2) {
    int x = _x + p2.getX();
    int y = _y + p2.getY();
    return Point(y, x);
}

void Point::operator=(Point p2) {
    _x = p2.getX();
    _y = p2.getY();
}

bool Point::operator==(Point p2) {
    if (_x == p2.getX() && _y == p2.getY()){
        return true;
    }
    return false;
}
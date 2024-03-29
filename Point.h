#pragma once

class Point {
    private:
        int _x;
        int _y;
    public:
        Point();
        Point(int y, int x);
        /*Getters*/
        int getX() { return _x; };
        int getY() { return _y; };
        /*Setters*/
        void setX(int newX);
        void setY(int newY);
        /*Operators*/
        Point operator+(Point p2);
        void operator=(Point p2);
        bool operator==(Point p2);
};
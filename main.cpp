#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <random>

#include "Map.h"
#include "Player.h"


#define PLAYERX_INI 3
#define PLAYERY_INI 8

using namespace std;

int main() {
    /* File contaning the level ASCII*/
    ifstream levelFile;
    levelFile.open("level1.txt");
    if (levelFile.fail()) {
        perror("level1.txt");
        return 1;
    }
    Map levelMap(&levelFile);
    levelFile.close();
    Player p1(Point(PLAYERY_INI, PLAYERX_INI));

    int row, col;
    initscr();				/* start the curses mode */
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr,row,col);
    curs_set(0);
    move(row - 1, 0);
    printw("ROWS: %d, COLS: %d",row, col );
    int input;
    bool endLevel = false;
    do {
        input = getch();
        move(0,0);
        switch (input)
        {
            case KEY_UP:
            case 'w':
                endLevel = levelMap.checkTile(&p1, Point(-1, 0));
                break;
            case 'a':
            case KEY_LEFT:
               endLevel = levelMap.checkTile(&p1, Point(0, -1));
                break;
            case KEY_DOWN:
            case 's':
               endLevel = levelMap.checkTile(&p1, Point(1, 0));
                break;
            case KEY_RIGHT:
            case 'd':
               endLevel = levelMap.checkTile(&p1, Point(0, 1));
                break;
        }
        if (endLevel)
            break;
        move(1, 0);
        levelMap.printMap();
        mvaddch(p1.getPosition().getY(), p1.getPosition().getX() - 1, '@');
    } while (input != 'E');
    
    refresh();
    getch();
    endwin();
    
    p1.printInfo();
    levelMap.printMonsters();

    return 0;
}
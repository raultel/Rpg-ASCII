#pragma once

#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <list>
#include <random>

#include "Player.h"
#include "Inventory.h"
#include "Monster.h"

using namespace std;

#define WIDTH 48
#define HEIGHT 10

#define PLAYER '@'
#define WALL '#'
#define GOBLIN 'G'
#define KOBOLD 'M'
#define WYVERN 'W'
#define AIR '.'
#define CHEST 'C'
#define ORC 'O'
#define EXIT 'E'
#define LOOT 'L'
#define K_DOOR 'K'
#define T_DOOR 'T'

class Map{
    private:
        /* Dungeon map ASCII */
        char _map[HEIGHT][WIDTH];
        list<Monster> _monsters;
        Inventory _loots;
        void readItems(ifstream *levelFile);
        void readMonsters(ifstream *levelFile);
        void searchMonsters(Monster monsterTemplate);
        void walkMonsters();
        void drawMonsters();
        Monster *findMonster(Point position);
        void removeMonster(Point position);
        void simulateCombat(Player *player, Monster *monster);
    public:
        Map(ifstream *levelFile);
        void printMap();
        bool checkTile(Player *player, Point dir);
        Inventory getLoots() { return _loots; }
        void printMonsters();
};
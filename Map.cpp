#include "Map.h"
#include <string>

int convertRow(int counter) {
    return counter / WIDTH;
}
int convertColumn(int counter) {
    return counter % WIDTH;
}

void Map::readItems(ifstream *levelFile) {
    int numberMonsters;
    *levelFile >> numberMonsters;
    char symbol;
    string name;
    int hp, strenght, ac;
    for (int i = 0; i < numberMonsters; i++) {
        int y,x,price;
        string name;
        *levelFile >> y;
        levelFile->get(); // ','
        *levelFile >> x;
        levelFile->get(); // ' '
        *levelFile >> price;
        levelFile->get(); // ' '
        getline(*levelFile, name);
        _loots.addItem(Item(name, price, Point(y, x)));
    }
}

void Map::readMonsters(ifstream *levelFile) {
    int numberMonsters;
    char symbol;
    string name;
    int hp, strenght, ac;
    *levelFile >> numberMonsters;
    //cout <<numberMonsters << endl;
    for (int i = 0; i < numberMonsters; i++) {
        *levelFile >> symbol;
        levelFile->get(); // ' '
        *levelFile >> hp;
        levelFile->get(); // ' '
        *levelFile >> strenght;
        levelFile->get(); // ' '
        *levelFile >> ac;
        levelFile->get(); // ' '
        getline(*levelFile, name);
        Monster monsterTemplate(symbol, name, hp, strenght, ac);
        searchMonsters(monsterTemplate);
    }
}

void Map::searchMonsters(Monster monsterTemplate) {
    char symbol = monsterTemplate.getSymbol();
    for (int i =0; i < HEIGHT; i++) {
        for (int j= 0; j < WIDTH; j++) {
            if (_map[i][j] == symbol) {
                _map[i][j] = '.';
                _monsters.push_back(monsterTemplate.copyMonster(Point(i,j)));
            }
        }
    }
}

void Map::printMonsters() {
    list<Monster>::iterator lit;
    for (lit = _monsters.begin(); lit != _monsters.end(); lit++) {
        lit->print();
    }
}

/* Puts the file into a char matrix*/
Map::Map(ifstream *levelFile) 
{
    char c;
    int i = 0;
    while((*levelFile).get(c)) {
        if (c == '*')
            break;
        if (c != '\n') {
            _map[convertRow(i)][convertColumn(i)] = c;
            cout << c;
            i++;
        }  else {
            cout << endl;
        }
    }
    string readString;
    getline(*levelFile, readString); /* Ignores the * line */
    readItems(levelFile);
    readMonsters(levelFile);

}

void Map::printMap() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            addch(_map[i][j]);
        }
        addch('\n');
    }
}

void Map::walkMonsters() {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist3(1, 3);
    list<Monster>::iterator lit;;
    for (lit = _monsters.begin(); lit != _monsters.end(); lit++) {
        if (dist3(rng) != 3) {
            continue;
        }
        int xBefore = lit->getPosition().getX();
        int yBefore = lit->getPosition().getY();
        int x = xBefore + dist3(rng) - 2;
        int y = yBefore + dist3(rng) - 2;
        if (x >= 1 && y >= 1 && x < WIDTH - 1 && y < HEIGHT - 1) {
            if (_map[y][x] == '.') {
                lit->setPosition(Point(y, x));
                _map[yBefore][xBefore] = '.';
            }
        }
    }
}

void Map::drawMonsters() {
    list<Monster>::iterator lit;
    for (lit = _monsters.begin(); lit != _monsters.end(); lit++) {
        Point position = lit->getPosition();
        _map[position.getY()][position.getX()] = lit->getSymbol();
    }
}

Monster *Map::findMonster(Point position) {
    list<Monster>::iterator lit;
    for (lit = _monsters.begin(); lit != _monsters.end(); lit++) {
        if (lit->getPosition() == position)
            return &(*lit);
    }
    return NULL;
}

void Map::simulateCombat(Player *player, Monster *monster) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist20(1, 20);
    /* Players attacks first */
    if (dist20(rng) + player->getStrenght() >= monster->getAC()){ 
        int dano = dist20(rng) % 6 + player->getStrenght();
        monster->takeDamage(dano);
        
        mvprintw(17, 0, "\t\t\t\t\t\t\t");
        mvprintw(17, 0, "Voce atacou %s e deu %d de dano\n", monster->getName().c_str(), dano);
        mvprintw(16, 0, "\t\t\t\t\t\t\t\t\t\t");
        mvprintw(16, 0, "Vida do %s: %d", monster->getName().c_str(), monster->getHP());
    }
    /* Monster's attack */
    if (dist20(rng) + monster->getStrenght() >= player->getAC()){ 
        int dano = dist20(rng) % 2 + monster->getStrenght();
        player->takeDamage(dano);
        mvprintw(18, 0, "\t\t\t\t\t");
        mvprintw(18, 0, "Voce foi atacado por %s e levou %d de dano\n", monster->getName().c_str(), dano);
    }
}

void Map::removeMonster(Point position) {
    list<Monster>::iterator lit;
    for (lit = _monsters.begin(); lit != _monsters.end(); lit++) {
        if (lit->getPosition() == position) {
            lit = _monsters.erase(lit);
        }
    }
}

bool Map::checkTile(Player *player, Point dir) {
    walkMonsters();
    drawMonsters();
    Point newPos = player->getPosition() + dir + Point(-1 , -1);
    char tile = _map[newPos.getY()][newPos.getX()];

    Item item("NULL", 0, Point(-1,-1));

    if (tile == 'M' || tile == 'O' || tile == 'W' || tile == 'G') {
        Monster *foundMonster = findMonster(newPos);
        simulateCombat(player, foundMonster);
        mvprintw(19, 0, "\t\t\t\t\t");
        if (foundMonster->getHP() <= 0) {
            mvprintw(19, 0, "Voce matou um %s\n", foundMonster->getName().c_str());
            removeMonster(newPos);
            _map[newPos.getY()][newPos.getX()] = '.';
        }
        if (player->getHP() <= 0) {
            mvprintw(17, 0, "\t\t\t\t\t");
            mvprintw(18, 0, "\t\t\t\t\t");
            mvprintw(19, 0, "\t\t\t\t\t");
            return true;
        }
    } else {
        mvprintw(17, 0, "\t\t\t\t\t");
        mvprintw(18, 0, "\t\t\t\t\t");
        mvprintw(19, 0, "\t\t\t\t\t");
    }
    
    switch (tile)
    {
    case 'M':
    case 'O':
    case 'W':
    case 'G':
        return false;
        break;
    case WALL:
        return false;
        break;
    case LOOT:
        item = _loots.getItem(newPos);
        player->addItem(item);
        _loots.removeItem(item.getName());
        _map[newPos.getY()][newPos.getX()] = '.';
        mvprintw(20, 0, "\t\t\t\t\t\t");
        mvprintw(20, 0, "Voce achou: %s", item.getName().c_str());
        break;
    case K_DOOR:
        if(player->getInventory().checkItem("Key k")) {
            _map[newPos.getY()][newPos.getX()] = '.';
        } else {
            return false;
        }
        break;
    case CHEST:
        _map[newPos.getY()][newPos.getX()] = '.';
        player->addGold(10);
        break;
    case T_DOOR:
        if(player->getInventory().checkItem("Key t")) {
            _map[newPos.getY()][newPos.getX()] = '.';
        } else {
            return false;
        }
        break;
    case EXIT:
        return true;
        break;
    default:
        //return false;
        break;
    }
    
    player->walk(dir);
    return false;
}
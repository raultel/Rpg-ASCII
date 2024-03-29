#include "Monster.h"

Monster::Monster(char symbol, string name, int hp, int strenght, int ac) {
    _name = name;
    _HP = hp;
    _strenght = strenght;
    _AC = ac;
    _position = Point(-1, -1);
    _symbol = symbol;
}

void Monster::takeDamage(int damage) {
    _HP -= damage;
}

void Monster::print() {
    cout << "[" << _name << "(" << _symbol << ")]\n";
    cout << "HP: " << _HP <<"\t";
    cout << "AC: " << _AC << "\t";
    cout << "strenght: " << _strenght << "\t";
    cout << "Position: " << _position.getY() << "," << _position.getX() << endl;
}

Monster Monster::copyMonster(Point position) {
    Monster newMonster(_symbol, _name, _HP, _strenght, _AC);
    newMonster.setPosition(position);
    return newMonster;
}
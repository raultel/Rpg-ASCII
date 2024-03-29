#include "Player.h"

Player::Player(Point position) {
    _position = position;
    _gold = 0;
    _AC = 14;
    _strenght = 3;
    _HP = 25;
}

void Player::walk(Point difference) {
    _position = (_position + difference);
}

void Player::addItem(Item newItem) {
    _inventory.addItem(newItem);
}

void Player::addGold(int gold) {
    _gold += gold;
}

void Player::takeDamage(int damage) {
    _HP -= damage;
}

void Player::printInfo(){
    cout << "[Player's inventory]\n";
    cout << "Gold: " << _gold;
    getInventory().printInventory();
    cout << "--------------------\n";
}
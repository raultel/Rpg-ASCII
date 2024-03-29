#include "Inventory.h"

void Inventory::printInventory() {
    cout << "\n--- START OF INVENTORY ---\n\n";
    list<Item>::iterator lit;
    int i = 1;
    for (lit = _items.begin(); lit != _items.end(); lit++) {
        cout << i << ". ";
        (*lit).print();
        i++;
    }
    cout << "\n-=-- END OF INVENTORY ----\n\n";
}

void Inventory::addItem(Item item) {
    list<Item>::iterator lit;
    for (lit = _items.begin(); lit != _items.end(); lit++) {
        if ((*lit).getName() == item.getName()) {
            (*lit).addOne();
            return;
        }
    }
     _items.push_back(item);
}

bool Inventory::removeItem(string itemName) {
    list<Item>::iterator lit;
    for (lit = _items.begin(); lit != _items.end(); lit++) {
        if ((*lit).getName() == itemName) {
            if ((*lit).getCount() == 1) {
                _items.erase(lit);
            } else{
                (*lit).removeOne();
            }
            return true;
        }
    }
    return false;
}

Item Inventory::getItem(Point position) {
    list<Item>::iterator lit;
    for (lit = _items.begin(); lit != _items.end(); lit++) {
        if ((*lit).getPosition() == position) {
            Item returnItem = (*lit);
            return returnItem;
        }
    }
    return Item("NULL", 0, Point(-1,-1));
}

bool Inventory::checkItem(string itemName) {
    list<Item>::iterator lit;
    for (lit = _items.begin(); lit != _items.end(); lit++) {
        if ((*lit).getName() == itemName)
            return true;
    }
    return false;
}
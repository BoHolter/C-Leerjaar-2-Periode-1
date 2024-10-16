#pragma once
#include<string>
#include "Item.h"
class Consumable :
    public Item

{

public:
    Consumable(std::string aName);
    ~Consumable();


private:
    std::string name;
    int health;
    int attackPower;
    int magic;
    int mana;

};


#include "Inventory.h"



Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(Item* anItem)
{
    items.push_back(anItem);
}

std::vector<Item*> Inventory::GetItems()
{
    return items;
}

void Inventory::RemoveItem(Item* anItem)
{
}

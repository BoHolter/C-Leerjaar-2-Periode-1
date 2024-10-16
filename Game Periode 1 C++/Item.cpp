#include "Item.h"

Item::Item(std::string aName) : name(aName)
{
}

// Destructor
Item::~Item()
{
}

// Getter implementation
std::string Item::GetName()
{
    return name;
}

// Setter implementation
void Item::SetName(std::string aName)
{
    name = aName;
}
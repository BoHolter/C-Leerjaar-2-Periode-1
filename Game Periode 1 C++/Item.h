#pragma once
#include <string>
class Item
{
public:
    // Constructor
    Item(std::string aName);

    // Destructor
    ~Item();

    // Getter for the name
    std::string GetName();

    // Setter for the name
    void SetName(std::string aName);

private:
    // Private member to store the name
    std::string name;
};

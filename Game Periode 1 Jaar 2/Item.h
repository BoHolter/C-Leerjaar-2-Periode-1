#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>


class Item {
public:
    string name;
    int effectValue;  // Bijvoorbeeld schade of HP-boost
    string type;      // "weapon", "potion" etc.

    Item(string n, int e, string t) : name(n), effectValue(e), type(t) {}
};

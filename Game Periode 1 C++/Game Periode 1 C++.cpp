// Game Periode 1 C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Inventory.h"
#include "Item.h"

int main()
{
    //Hier begint mijn programma!
    Inventory inv; //aanmaken inventory
    for (int i = 0; i < 99; i++) { //99x loopen
        Item stone("Stone"); //stenen aanmaken
        inv.AddItem(&stone);//deze stenen toevoegen aan de inv.
    }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

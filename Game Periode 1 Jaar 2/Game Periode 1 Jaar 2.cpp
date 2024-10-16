#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>



// Klasse voor items zoals wapens en potions
class Item {
public:
   std:: string name;
    int effectValue;  // Bijvoorbeeld schade of HP-boost
   std:: string type;      // "weapon", "potion" etc.

    Item(std::string n, int e, std::string t) : name(n), effectValue(e), type(t) {}
};

// Klasse voor het karakter (speler of vijand)
class Character {
public:
   std:: string name;
    int health;
    int strength;
   std:: string weapon;
    int weaponDamage;

    Character(std::string n, int h, int s, std::string w, int wd)
        : name(n), health(h), strength(s), weapon(w), weaponDamage(wd) {}

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    void attack(Character& enemy) {
       std:: cout << name << " valt " << enemy.name << " aan met " << weapon << " en doet " << strength + weaponDamage << " schade!" << std::endl;
        enemy.takeDamage(strength + weaponDamage);
    }

    void heal(int amount) {
        health += amount;
        std::cout << name << " herstelt " << amount << " HP!" << std::endl;
    }
};

// Inventory systeem voor items
class Inventory {
public:
   std:: vector<Item> items;

    void addItem(Item item) {
        items.push_back(item);
        std::cout << item.name << " is toegevoegd aan je inventory." << std::endl;
    }

    void showInventory() {
        if (items.empty()) {
            std::cout << "Je inventory is leeg." << std::endl;
        }
        else {
           std:: cout << "Je inventory bevat de volgende items:" << std::endl;
            for (size_t i = 0; i < items.size(); ++i) {
                std::cout << i + 1 << ". " << items[i].name << " (Effect: " << items[i].effectValue << ", Type: " << items[i].type << ")" << std::endl;
            }
        }
    }

    // Gebruik een item (healing potion)
    void useItem(Character& player, int index) {
        if (index < 0 || index >= items.size()) {
            std::cout << "Ongeldige keuze." << std::endl;
            return;
        }

        Item item = items[index];
        if (item.type == "potion") {
            player.heal(item.effectValue);
            items.erase(items.begin() + index);  // Verwijder de potion na gebruik
        }
        else {
            std::cout << "Dit item kan niet gebruikt worden." << std::endl;
        }
    }
};

// Helper functie voor het genereren van willekeurige nummers
int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Spel startmenu
void startMenu() {
   std:: cout << "Welkom bij de RPG Game!" << std::endl;
    std::cout << "1. Start Spel" << std::endl;
   std:: cout << "2. Afsluiten" << std::endl;
}

// Functie voor het selecteren van een wapen
std::string selectWeapon() {
    std::cout << "Kies je wapen:" << std::endl;
    std::cout << "1. Zwaard (10 schade)" << std::endl;
    std::cout << "2. Speer (15 schade)" << std::endl;
    std::cout << "3. Zweep (7 schade)" << std::endl;
    std::cout << "4. Vuisten (5 schade)" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: return "Zwaard";
    case 2: return "Speer";
    case 3: return "Zweep";
    case 4: return "Vuisten";
    default: return "Vuisten";  // Default wapen
    }
}

// Functie om het wapen schade te bepalen
int getWeaponDamage(const std::string& weapon) {
    if (weapon == "Zwaard") return 25;
    if (weapon == "Speer") return 20;
    if (weapon == "Zweep") return 15;
    return 5;  // Vuisten
}

// Willekeurig item drop na een gewonnen ronde
void dropItem(Inventory& inventory) {
    int dropChance = random(1, 100);  // Willekeurige kans voor een drop
    if (dropChance <= 50) {  // 50% kans op een potion
        Item potion("Healing Potion", random(20, 30), "potion");
        inventory.addItem(potion);
    }
    else {  // 50% kans op een wapen
        std::vector<Item> weapons = {
            Item("Bijl", 18, "weapon"),
            Item("Dolken", 18, "weapon"),
            Item("Magische Staf", 20, "weapon")
        };
        int randomIndex = random(0, weapons.size() - 1);
        inventory.addItem(weapons[randomIndex]);
    }
}

// Gevechtslus tussen speler en vijand
bool battle(Character& player, Character& enemy, Inventory& inventory) {
    while (player.health > 0 && enemy.health > 0) {
        std::cout << "\n--- Gevechtsronde ---" << std:: endl;
       std:: cout << player.name << " HP: " << player.health << " | " << enemy.name << " HP: " << enemy.health << std::endl;

       std:: cout << "Kies je actie:" << std::endl;
       std:: cout << "1. Aanvallen" << std::endl;
       std:: cout << "2. Defenden" << std::endl;
       std:: cout << "3. Inventory bekijken" <<std:: endl;
       std:: cout << "4. Gebruik item" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            player.attack(enemy);
            if (enemy.health > 0) {
                enemy.attack(player);
            }
        }
        else if (choice == 2) {
           std:: cout << player.name << " verdedigt zichzelf!" << std::endl;
            int damage = std::max(0, (enemy.strength + enemy.weaponDamage) / 2);  // Verminderde schade
            player.takeDamage(damage);
           std:: cout << player.name << " ontvangt " << damage << " schade door verdedigen." << std::endl;
        }
        else if (choice == 3) {
            inventory.showInventory();
        }
        else if (choice == 4) {
            inventory.showInventory();
           std:: cout << "Kies een item om te gebruiken: ";
            int itemChoice;
           std:: cin >> itemChoice;
            inventory.useItem(player, itemChoice - 1);  // Gebruik het item
        }
        else {
           std:: cout << "Ongeldige keuze, probeer opnieuw." << std::endl;
        }
    }

    if (player.health > 0) {
        std::cout << player.name << " heeft de vijand verslagen!" << std::endl;
        return true;
    }
    else {
        std::cout << player.name << " is verslagen." << std::endl;
        return false;
    }
}

// Functie om HP te herstellen na een gewonnen ronde
void healAfterRound(Character& player) {
    int healAmount = random(10, 20); // Herstel een willekeurige hoeveelheid tussen 10 en 20 HP
    player.health += healAmount;
    std::cout << player.name << " herstelt " << healAmount << " HP na de ronde!" << std::endl;
}

int main() {
    srand(time(0));

    // Startmenu tonen
    int menuChoice;
    startMenu();
    std::cin >> menuChoice;

    if (menuChoice == 2) {
        std::cout << "Spel afgesloten." << std::endl;
        return 0;
    }

    // Speler creëren
    std::string playerName;
    std::cout << "Voer je naam in: ";
    std::cin >> playerName;
    int playerAge;
    std::cout << "Voer je leeftijd in: ";
    std::cin >> playerAge;

    std::string playerWeapon = selectWeapon();
    int playerWeaponDamage = getWeaponDamage(playerWeapon);
    Character player(playerName, 100, 10, playerWeapon, playerWeaponDamage);

    // Inventory aanmaken
    Inventory playerInventory;

    // Gevechten met verschillende vijanden
    std::vector<Character> enemies = {
        Character("Goblin", 50, 5, "Vuisten", 5),
        Character("Orc", 80, 8, "Knots", 10),
        Character("Troll", 100, 12, "Mace", 15),
        Character("Baas Draak", 200, 20, "Vuur Adem", 25)  // Boss battle
    };

    // Begin gevechtsronde
    bool gameWon = true;
    for (size_t i = 0; i < enemies.size(); ++i) {
        std::cout << "\n--- Ronde " << i + 1 << " ---" << std::endl;
        if (!battle(player, enemies[i], playerInventory)) {
            gameWon = false;
            break;
        }
        if (i < enemies.size() - 1) {
            healAfterRound(player);  // HP herstellen tussen gevechten
            dropItem(playerInventory);  // Voeg willekeurige drops toe
        }
    }
}
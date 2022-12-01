#include "Inventory.h"
#include "Treasure.h"
#include "Weapon.h"
#include "Cookware.h"

#include <iostream>
#include <vector>

using namespace std;

Inventory::Inventory()
{
    vector<Treasure> treasure;
    treasures_ = treasure;

    vector<Cookware> cookware;
    cookwares_ = cookware;

    vector<Weapon> weapons;
    weapons_ = weapons;

    gold_ = 100;
    armor_ = 0;
    ingredients_ = 0;
}
Inventory::Inventory(vector<Treasure> treasures, vector<Cookware> cookwares, vector<Weapon> weapons, int gold, int armor, int ingredients)
{
    treasures_ = treasures;
    cookwares_ = cookwares;
    weapons_ = weapons;

    gold_ = gold;
    armor_ = armor;
    ingredients_ = ingredients;
}


        //getters
vector<Treasure>& Inventory::getTreasureList()
{
    return treasures_;
}

void Inventory::printTreasureList()
{
    if(treasures_.size() == 0)
    {
        cout << "There is currently no treasure stored in the inventory." << endl;
    }

    for(int i = 0; i < treasures_.size(); i++)
    {
        cout << treasures_[i].getTreasureName() << ", " << treasures_[i].getTreasurePrice() << endl;
    }
}

vector<Cookware>& Inventory::getCookwareList()
{
    return cookwares_;
}
void Inventory::printCookwareList()
{
    if(cookwares_.size() == 0)
    {
        cout << "There is currently no cookware stored in the inventory." << endl;
    }

    for(int i = 0; i < cookwares_.size(); i++)
    {
        cout << cookwares_[i].getCookName() << ", " << cookwares_[i].getCookPrice() << ", " << cookwares_[i].getCookBreak() << endl;
    }
}
            
vector<Weapon>& Inventory::getWeaponList()
{
    return weapons_;
}
void Inventory::printWeaponList()
{
    if(weapons_.size() == 0)
    {
        cout << "There are currently no weapons stored in the inventory." << endl;
    }

    for(int i = 0; i < weapons_.size(); i++)
    {
        cout << weapons_[i].getWeaponName() << ", " << weapons_[i].getWeaponPrice() << ", " << weapons_[i].getWeaponDamage() << endl;
    }
}

int Inventory::getNumGold() const
{
    return gold_;
}
int Inventory::getNumArmor() const
{
    return armor_;
}
int Inventory::getNumIngredients() const
{
    return ingredients_;
}

            // more specialized
int Inventory::getNumTreasure(string treasure_name)
{
    int treasure_count = 0;

    for(int i = 0; i < treasures_.size(); i++)
    {
        if(treasures_[i].getTreasureName() == treasure_name)
        {
            treasure_count++;
        }
    }
    return treasure_count;
}
int Inventory::getNumCookware(string cookware_name)
{
    int cookware_count = 0;

    for(int i = 0; i < cookwares_.size(); i++)
    {
        if(cookwares_[i].getCookName() == cookware_name)
        {
            cookware_count++;
        }
    }
    return cookware_count++;
}
int Inventory::getNumWeapon(string weapon_name)
{
    int weapon_count = 0;

    for(int i = 0; i < weapons_.size(); i++)
    {
        if (weapons_[i].getWeaponName() == weapon_name)
        {
            weapon_count++;
        }
    }
    return weapon_count;
}


//setters
            // thinking that for the vectors of different items, I will just use vector functions from the library like push back

void Inventory::setGold(int gold)
{
    int gold_check = gold;

    if(gold_check < 0)
    {
        gold_check = 0;
    }

    gold_ = gold_check;
}
void Inventory::setArmor(int armor)
{
    int armor_check = armor;

    if(armor_check < 0)
    {
        armor_check = 0;
    }

    armor_ = armor_check;
}
void Inventory::setIngredients(int ingredients)
{
    int ingredient_check = ingredients;

    if(ingredient_check < 0)
    {
        ingredient_check = 0;
    }

    ingredients_ = ingredient_check;
}

void Inventory::setCookwareAt(Cookware c, int position)
{
    int position_check = position;

    while(position_check < 0 || position_check >= cookwares_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    cookwares_[position_check] = c;
}

void Inventory::setWeaponAt(Weapon w, int position)
{
    int position_check = position;

    while(position_check < 0 || position_check >= weapons_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    weapons_[position_check] = w;
}

void Inventory::setTreasureAt(Treasure t, int position)
{
    int position_check = position;

    while(position_check < 0 || position_check >= treasures_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    treasures_[position_check] = t;
}

//special
void Inventory::inventoryDisplay()
{
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << gold_ << endl;
    cout << "| Ingredients | " << ingredients_ << endl;
    cout << "| Cookware    | P: " << getNumCookware("Ceramic Pot") << " | F: " << getNumCookware("Frying Pan") << " | C: " << getNumCookware("Cauldron") << endl;
    cout << "| Weapons     | C: " << getNumWeapon("Club of Christ") << " | S: " << getNumWeapon("Spear of Truth") << " | R: " << getNumWeapon("Rapier of Ragnarok") << " | A: " << getNumWeapon("Axe of Alabasta") << " | L: " << getNumWeapon("Zoro's Longsword") << endl;
    cout << "| Armor       | " << armor_ << endl;
    cout << "| Treasures   | S: " << getNumTreasure("Silver Ring") << " | R: " << getNumTreasure("Ruby Necklace") << " | E: " << getNumTreasure("Emerald Bracelet") << " | D: " << getNumTreasure("Diamond Circlet")  << " | N: " << getNumTreasure("Netherite Goblet") << endl;
    cout << "+-------------+" << endl;
}

void Inventory::removeTreasure(int position)
{
    if(treasures_.size() == 0)
    {
        cout << "There are no treasures to remove." << endl;
        return;
    }

    int position_check = position;

    while (position_check < 0 && position_check >= treasures_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    treasures_.erase(treasures_.begin() + position);

    //cout << "Update list of treasures: " << endl;

   //printTreasureList();
}

void Inventory::removeWeapon(int position)
{
    if(weapons_.size() == 0)
    {
        cout << "There are no weapons to remove." << endl;
        return;
    }

    int position_check = position;

    while (position_check < 0 && position_check >= weapons_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    weapons_.erase(weapons_.begin() + position);

    //cout << "Update list of weapons: " << endl;

    //printWeaponList();
}

void Inventory::removeCookware(int position)
{
    if(cookwares_.size() == 0)
    {
        cout << "There is no cookware to remove." << endl;
        return;
    }

    int position_check = position;

    while (position_check < 0 && position_check >= cookwares_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    cookwares_.erase(cookwares_.begin() + position);

    //cout << "Update list of cookware: " << endl;

    // printCookwareList();
}

void Inventory::addWeapon(Weapon w)
{
    if(weapons_.size() == 5)
    {
        cout << "No more weapons can be added to the inventory." << endl;
    }
    else
    {
        weapons_.push_back(w);
        cout << "The weapon has been successfully added to the inventory." << endl;
    }
}

void Inventory::addCookware(Cookware c)
{
    if(cookwares_.size() == 5)
    {
        cout << "No more cookware can be added to the inventory." << endl;
    }
    else
    {
        cookwares_.push_back(c);
        cout << "The cookware has been successfully added to the inventory." << endl;
    }
}

void Inventory::addTreasure(Treasure t) // no conditional for treasure because I want the party to have as much treasure as possible, limited to 5 weapons / cookware tho
{
    treasures_.push_back(t);
    cout << "The treasure has been successfully added to the inventory" << endl;
}

//I may consider creating add <object> functions like addWeapon, we'll see
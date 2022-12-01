#include "Weapon.h"
#include <iostream>

using namespace std;

Weapon::Weapon()
{
    price_ = 0;
    name_ = "";
    damage_ = 0;
}
Weapon::Weapon(string name, int price, int damage)
{
    int price_check = price;
    int damage_check = damage;

    while (damage_check < 0)
    {
        cout << "Please enter a positive damage value." << endl;
        cin >> damage_check;
    }

    while(price_check < 0)
    {
        cout << "Please enter a positive price." << endl;
        cin >> price_check;
    }


    price_ = price_check;
    name_ = name;
    damage_ = damage_check;
}

//getters
int Weapon::getWeaponDamage() const
{
    return damage_;
}

int Weapon::getWeaponPrice() const
{
    return price_;
}
string Weapon::getWeaponName() const
{
    return name_;
    
}


// setters
void Weapon::setWeaponDamage(int damage)
{
    int damage_check = damage;

    while (damage_check < 0)
    {
        cout << "Please enter a positive damage value." << endl;
        cin >> damage_check;
    }

    damage_ = damage_check;
}


void Weapon::setWeaponPrice(int price)
{
    int price_check = price;

    while(price_check < 0)
    {
        cout << "Please enter a positive price." << endl;
        cin >> price_check;
    }

    price_ = price_check;
}
void Weapon::setWeaponName(string name)
{
    name_ = name;
}



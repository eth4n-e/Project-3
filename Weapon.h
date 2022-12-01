#include <iostream>

using namespace std;

#ifndef WEAPON_H
#define WEAPON_H

//rationale for weapon class is that a party will possess weapons
// while which player has a weapon doesn't necessarily matter
// a weapon has more unique properties than the other items
// not creating data members which are like the weapons themselves
// want to be able to read from a weapon file to create weapon objects
// will use split function

class Weapon
{
    private:
        int price_;
        string name_;
        int damage_;

    public:

        Weapon();
        Weapon(string name, int price, int damage);

        //getters
        int getWeaponPrice() const;
        string getWeaponName() const;
        int getWeaponDamage() const;

        // setters
        void setWeaponPrice(int price);
        void setWeaponName(string name);
        void setWeaponDamage(int damage);

};

#endif
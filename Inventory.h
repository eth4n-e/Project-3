#include "Treasure.h"
#include "Weapon.h"
#include "Cookware.h"

#include <iostream>
#include <vector>

using namespace std;

#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
    private:
        vector<Treasure> treasures_;
        vector<Cookware> cookwares_;
        vector<Weapon> weapons_;

        int gold_;
        int armor_;
        int ingredients_;

    public:

        //constructors
        Inventory();
        Inventory(vector<Treasure> treasures, vector<Cookware> cookwares, vector<Weapon> weapons, int gold, int armor, int ingredients);


        //getters
            vector<Treasure>& getTreasureList();
                void printTreasureList();

            vector<Cookware>& getCookwareList();
                void printCookwareList();
            
            vector<Weapon>& getWeaponList();
                void printWeaponList();

            int getNumGold() const;
            int getNumArmor() const;
            int getNumIngredients() const;

            // more specialized
            int getNumTreasure(string treasure_name);
            int getNumCookware(string cookware_name);
            int getNumWeapon(string weapon_name);


        //setters
            // thinking that for the vectors of different items, I will just use vector functions from the library like push back

            void setGold(int gold);
            void setArmor(int armor);
            void setIngredients(int ingredients);

            void setCookwareAt(Cookware c, int position);
            void setWeaponAt(Weapon w, int position);
            void setTreasureAt(Treasure t, int position);

        //special
            void inventoryDisplay();
            void removeTreasure(int position);
            void removeWeapon(int position);
            void removeCookware(int position); 

            void addWeapon(Weapon w); // adds a weapon to the back of the list
            void addCookware(Cookware c); 
            void addTreasure(Treasure t);

};

#endif
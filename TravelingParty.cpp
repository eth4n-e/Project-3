#include "TravelingParty.h"
#include "Player.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Cookware.h"
#include "Treasure.h"
#include <iostream>
#include <vector>

using namespace std;

// change getObjects functions so that they cout the contents of the array rather than get the value

/* Data members

int rooms_;
        int keys_;
        int coins_;
        int ingredients_;
        int armor_;

        vector<Player> players_; //vector to store players

        vector<Weapon> weapons_; // vector to store weapons
        //vector<int> weapon_count_;

        vector<Item> items_; //vector to store treasure (mainly, will generalize it in case)
        //vector<int> item_count_;

        vector<Cookware> cookware_; // vector to store cookware

*/
// print functions work, before final date add to the cout statements with things like "price:" << price

TravelingParty::TravelingParty()
{
    vector<Player> group;
    players_ = group;

    //Inventory inventory;
    inventory_ = Inventory();

    rooms_ = 0;
    keys_ = 0;
}


TravelingParty::TravelingParty(vector<Player> player, Inventory inventory, int rooms, int keys)
{
    for(int i = 0; i < player.size(); i++)
    {
        players_.push_back(player[i]);
    }

    inventory_ = inventory;

    rooms_ = rooms;
    keys_ = keys;
    
}



//getters
void TravelingParty::printPlayerList()
{
    if(players_.size() == 0)
    {
        cout << "There are currently no players stored." << endl;
    }
    else 
    {
        for(int i = 0; i < players_.size(); i++)
        {
            cout << players_[i].getName() << ", " << players_[i].getFullness() << endl;
        }
    }
}
vector<Player>& TravelingParty::getPlayerList() // return vector of players
{
    return players_;
}

Player& TravelingParty::getPlayer(int position)
{
    int position_check = position;

    while(position_check < 0 && position_check >= players_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    return players_[position_check];
}
        

int TravelingParty::getNumRooms() const
{
    return rooms_;
}
int TravelingParty::getNumKeys() const
{
    return keys_;
}

Inventory& TravelingParty::getInventory()
{
    return inventory_;
}



//setters

void TravelingParty::setPlayerAt(Player p, int position)
{
        int position_check = position;

        while(position_check < 0 && position_check >= players_.size())
        {
            cout << "Please enter a position in bounds." << endl;
            cin >> position_check;
        }

        players_[position_check] = p;
        
}

void TravelingParty::setNumRooms(int rooms)
{
    rooms_ = rooms;
}
void TravelingParty::setNumKeys(int keys)
{
    keys_ = keys;
}

void TravelingParty::setInventory(Inventory i)
{
    inventory_ = i;
}

// other

void TravelingParty::addPlayer(Player p) // will add object to back of list
{
    if(players_.size() == 5)
    {
        cout << "The group is at capacity. No players cna be added." << endl;
        
    }
    else
    {
        players_.push_back(p);
        cout << "Player has been successfully added." << endl;

    }
} 

void TravelingParty::removePlayer(int position) // will remove last object
{
    if(players_.size() == 1)
    {
        return;
    }

    int position_check = position;
    while(position_check < 0 && position_check >= players_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }
    if(position_check == 0)
    {
        cout << "There are no players to remove." << endl;
        return;
    }

    players_.erase(players_.begin() + position_check);
    



   // printPlayerList();
}

void TravelingParty::checkFullness()
{
    /*
        if(players_[position].getFullness() == 0)
        {
            return true;
        }
        else 
        {
            return false;
        }
    */

   for(int i = 0; i < players_.size(); i++)
   {
        if(players_[i].getFullness() == 0)
        {
            cout << "OH NO! " << players_[i].getName() << " is on the brink of starvation" << endl;
            cout << "You should cook and eat some food!" << endl;
        }
   }

   return;
}
/*vector<Weapon> TravelingParty::removeWeapon(int position) may use this in inventory class
{
    int position_check = position;
    while(position_check < 0 && position_check > weapons_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    weapons_.erase(weapons_.begin() + position_check);

    return weapons_;
}

vector<Item> TravelingParty::removeItem(int position) 
{
    int position_check = position;
    while(position_check < 0 && position_check > items_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    items_.erase(items_.begin() + position_check);

    return items_;
}

vector<Cookware> TravelingParty::removeCookware(int position)
{
    int position_check = position;
    while(position_check < 0 && position_check > cookware_.size())
    {
        cout << "Please enter a position in bounds." << endl;
        cin >> position_check;
    }

    cookware_.erase(cookware_.begin() + position_check);

    return cookware_;
}
*/

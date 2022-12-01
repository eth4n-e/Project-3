#include "Player.h"
#include "Weapon.h"
#include "Cookware.h"
#include "Treasure.h"
#include "Inventory.h"
#include <iostream>
#include <vector>

using namespace std;

#ifndef TRAVELINGPARTY_H
#define TRAVELINGPARTY_H

class TravelingParty
{
    private:
        
        int rooms_;
        int keys_;

        Inventory inventory_;

        vector<Player> players_; //vector to store players


        /*
        don't think I need weapon count or item count anymore because
        because the equation which determines attacking power for weapon class 
        */  

       // also need functions for each item type which returns them as a vector to be used in dungeon class
        
    public:

        //constructors
        TravelingParty();
        TravelingParty(vector<Player> player, Inventory inventory, int rooms, int keys);


        //getters
        int getNumRooms() const;
        int getNumKeys() const;

        vector<Player>& getPlayerList();
        Player& getPlayer(int position);

        //vector<bool> getPlayersStatus() const;
        //void setPlayerStatus(bool status, int index);

        Inventory& getInventory();
        void setInventory(Inventory i);

        //setters

        void setPlayerAt(Player p, int position);

        void setNumRooms(int rooms);
        void setNumKeys(int keys);

        //other
        void addPlayer(Player p);
        void removePlayer(int position);

        void printPlayerList();

        void checkFullness();
        // want to check the fullness of every player in take turn function
        // will have this running on a loop or could implement the loop in the function to check every players fullness
        // will return true if a player is on the brink of death - 0 fullness
        // in this way, I can call take turn again and if the fullness is still 0, the player dies
        // going to return a vector of player type, this way if multiple player's fullness is 0, they will all be stored in a vector

        // also going to create a vector type bool which stores each player's condition
        // the reason I think this will be useful is because in the event that the party leader (position 0) dies to fullness
        // I think that fullness drop is the only way they can die besides sorcerer anger reaching 100
        // I can set their alive state to false and then I can have a check which sees if the alive state at index 0 is false, which will set game end
        // may not need this
        /*
            In main I think I will have a vector which upon each loop is filled with the players whose fullness is at 0
            from there I can simply check if the player at index 0 of this vector has a name which matches the party leader
            
        
        */

};      

#endif
#include "Monster.h"
#include "Player.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Cookware.h"
#include "Treasure.h"
#include "TravelingParty.h"
#include "Dungeon.h"
#include "Map.h"

#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

int main()
{
    string party_leader_name;
    string member_name;

    Dungeon dungeon;

   // dungeon.readMonsters("monsters.txt");
    //dungeon.readRiddles("riddles.txt");

    /*
    for(int i = 0; i < 20; i++)
    {
        vector<string> riddles = dungeon.returnRiddleRow(i);

        for(int j = 0; j < riddles.size(); j++)
        {
            cout << riddles[j] << " ANSWER TO RIDDLE:";
        }
        cout << endl;
    }

    for(int i = 0; i < 5; i++)
    {
        vector<Monster> monsters = dungeon.returnMonsterRow(i);

        for(int j = 0; j < monsters.size(); j++)
        {
            cout << monsters[j].getName() << endl;
            cout << monsters[j].getDifficulty() << endl;
        }
    }
    
    vector<Monster> sorcerer = dungeon.returnMonsterRow(5);

    for(int z = 0; z < sorcerer.size(); z++)
    {
        cout << sorcerer[z].getName() << " | " << sorcerer[z].getDifficulty() << endl;
    }
*/
   dungeon.mapGeneration();


    cout << "Welcome to the Dungeon!" << endl;
    cout << "What is your name?" << endl;
    cin >> party_leader_name;

    dungeon.getParty().addPlayer(Player(party_leader_name, 50));

    cout << "Don't fret, you will not be alone on this journey." << endl;
    cout << "Please enter the names of your fellow comrades:" << endl;

    for(int i = 1; i < 5; i++)
    {
        cout << "Team member " << i << ":" << endl;
        cin >> member_name;

        dungeon.getParty().addPlayer((Player(member_name, 50)));
    }

    dungeon.displayStats();

    cout << "hmmmmm, your inventory looks a little empty. Let me take you to the merchant to stock up on some goods before your arduous journey." << endl;

    cout << "Between the 5 of you, you have 100 gold pieces." << endl;
    cout << "You will need to spend the some of your money on the following items:" << endl;

    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl;
    cout << "- COOKWARE. If you want to cook, you have to have cookware first." << endl;
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl;

    cout << "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way. But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;

    dungeon.visitMerchant(0);

    do 
    {
        dungeon.displayStats();

        dungeon.getMap().displayMap();

        dungeon.takeTurn();

        dungeon.getParty().checkFullness();

        /*
        // I think I'm getting a seg fault from this
        // if no players have 0 fullness, then status_check is empty thus comparing the value at index 0 would not exist
        if(status_check[0].getName() == dungeon.getParty().getPlayer(0).getName())
        {
            // debating having check fullness return vector of players
            // may just have check fullness return a vector of bools
            // if fullness is 0 the bool will be false
            // each player in the party will have a boolean associated with them, this I feel makes it easier
            // make sure that in removePlayer I would also remove the boolean associated with the player
            dungeon.getParty().removePlayer(0);
        }
        */

        vector<int> index;

        for(int i = 0; i < dungeon.getParty().getPlayerList().size(); i++)
        {
            if(dungeon.getParty().getPlayer(i).getFullness() == 0)
            {
                index.push_back(i);
            }
        }

        if(index.size() > 0)
        {
            dungeon.takeTurn();

            for(int j = 0; j < index.size(); j++)
            {
                if(dungeon.getParty().getPlayer(index[j]).getFullness() == 0)
                {
                    if(index[j] == 0)
                    {
                        dungeon.setGameOverStatus(true);
                        
                        cout << "You Died! There is no one fit to lead the team! The game must end!" << endl;
                        
                    }
                    else
                    {
                        dungeon.getParty().removePlayer(index[j]);

                        cout << "OH NO! " << dungeon.getParty().getPlayer(index[j]).getName() << " has died of hunger! Your party size has reduced to " << dungeon.getParty().getPlayerList().size() << " members." << endl;
                    }
                }
            }

        }

        bool isGameOver = dungeon.checkGameEnd();

    } while(dungeon.isGameOver() != true);

    dungeon.displayFinalStats();



    //dungeon.getMap().displayMap();

    //dungeon.takeTurn();

    

    return 0;
}
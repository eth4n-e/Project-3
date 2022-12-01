#include "Player.h"
#include "TravelingParty.h"
#include "Cookware.h"
#include "Weapon.h"
#include "Inventory.h"
#include "Monster.h"
#include "Map.h"
#include <vector>
#include <cctype>
#include <iostream>
#include <fstream>

#ifndef DUNGEON_H
#define DUNGEON_H

using namespace std;

/*
Might need some sort of read file function
Reason for need: may have to read from text files (for instance with initializing the vector of monsters, items, and weapons)
- use read file function in combination with split function to create new objects depending on the split outcome
- want to have access to all the other class member functions so makes sense to belong in dungeon class
*/

//ensure that the Player is always entered as the first index of the traveling party


class Dungeon 
{
    private:
    Map map_;

    TravelingParty tp_;

    vector<vector<Monster>> monsters_;
    vector<vector<string>> riddles_;

    int sorcerer_anger_;
    int turn_track_; // going to use this to keep track of the number of turns taken, will prove useful for when a player fullness reaches 0 because they die the next turn if their fullness has not increased
    int num_monsters_defeated_;
    int num_explored_spaces_;

    bool game_over_;

    // considering also creating a readRiddles function
    // in this instance, I would make a data member which would be a 2d vector of strings
    // the number of rows would correspond to the number of lines in the file
    // and each row would have two columns, one for the riddle question, and the other for the answer
    // would ensure I only have to read the file one time, no need to overwrite it everytime upon NPC function call
    // and managing what riddles have been asked would be easier
    // thinking of making this public, so I can call function by dungeon object
    

    public:

    // constructors

    Dungeon();
    // don't think I will use a parametrized constructor, will only use setters, getters, and other functions to ensure game is built

    
    Map& getMap();

    TravelingParty& getParty();

    int getAngerLevel() const;
    
    int getNumRoomsExplored() const;
    int getNumTurns() const;
    int getMonstersDefeated() const;

    void setGameOverStatus(bool game_condition);
    bool isGameOver() const;


    // still not sure if I will have as a function, function will likely just check conditions
    // of the game to ensure it is not over yet
    bool checkGameEnd();

    bool doorPuzzle();
    
    void readMonsters(string file_name);
    void readRiddles(string file_name);

    vector<Monster> returnMonsterRow(int row);
    vector<string>& returnRiddleRow(int row);

    void displayFinalStats();


    // calculate the outcome of the fight and use
    bool fight(int num_rooms);

    /*Idea:
    - use several random number generators
    - first, place position of Exit
    --- exit position will be determined by a random number 0 through 11 (indexes of the final row)
    - Then, create random positions for NPC and rooms whose row and column cannot be equal to the exit position and must be before
    - use functions of the map class like isRoom or isNPC to ensure that multiple rooms are not assigned to a single position
    - I believe I could accomplish this using a nested loop structure or even a singular loop
    - to simplify things, I will not place any room or NPC on the last row where the exit is
    ---- especially rooms, but maybe will have NPCS on last row (could do an if condition which checks the random column and row output and makes sure location would be before the exit)
    */
    void mapGeneration();

    /* Idea:
    - have menu/status update running on do while loop, menu will print out at the very beginning
    - first display status update
    - print map using map display
    - Allow the player five options: move, investigate, pick a fight, cook and eat, or give up
    - prompt user for input
    - switch statement based on integer selection
    - besides move, maybe implement functions for each option 1-4
    --- overall goal: compartmentalize each option and action of a turn into smaller functions to maximize organization and minimize lines within the actual take turn function
    ---- in essence, create functions to implement the actions and consolidate in take turn function
    - could maybe have take turn take a boolean which the function will check, boolean will only be false when the game is over or won
    - my thought that take turn should take some parameter
    - thinking that I should pass the players position to the function
    - this is because the actions a player can do depends on where the player is
    - Ex: actions on normal space differ from available actions on a room
    - function may not need parameters, because I can use getters of map class to get such info
    */
    void takeTurn();
    void misfortuneKey(); // should probably take some parameter
    /*
    separate stat display and inventory display into two different functions 
    */

    void misfortuneMain();

    void visitMerchant(int num_rooms); // should take a parameter (thinking number of room's cleared)
    void NPC();
    void displayStats(); // will be an edited version of the menu / status display

    void removeMonster(int row, int col);
    void removeRiddle(int row, int col);
    
};

#endif
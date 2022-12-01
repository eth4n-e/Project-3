#include "Dungeon.h"
#include "TravelingParty.h"
#include "Player.h"
#include "Weapon.h"
#include "Cookware.h"
#include "Inventory.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <ctime>

using namespace std;

int split(string input_string, char separator, string string_arr[], int arr_size)
{
    int num_splits = 0;

    int input_length = input_string.length();

    int index = 0;

    int delimiter = 0;
    
    if (input_string == "")
    {
        return 0;
    }

    for(int j = 0; j < input_length; j++)
    {
        if (input_string[j] == separator)
        {
            delimiter = j;
            string_arr[num_splits] = input_string.substr(index, delimiter - index);
            num_splits++;
            index = j+1;
        }
        if(num_splits == arr_size)
        {
            return -1;
        }

    }

    // for loop will account for the substrings before the last delimiter appears
    // this will add the last substring to the array
    string_arr[num_splits] = input_string.substr(delimiter+1);
    

    if(num_splits == 0)
    {
        string_arr[0] = input_string;
        return 1;
    }

    return num_splits + 1;
    
}

Dungeon::Dungeon() // debating between a parametrized constructor or default
{
    
    map_.resetMap();

    TravelingParty tp;
    tp_ = tp;

/*
    for(int i = 0; i < 20; i++)
    {
        vector<string> empty;
        for(int j = 0; j < 2; j++)
        {
            empty.push_back(" ");
        }
        riddles_.push_back(empty);
    }


    for(int i = 0; i < 5; i++)
    {
        vector<Monster> temp;
        for(int j = 0; j < 4; j++)
        {
            temp.push_back(Monster());
        }
        monsters_.push_back(temp);
    }
    vector<Monster> last;
    last.push_back(Monster());

    monsters_.push_back(last);
 */

    readRiddles("riddles.txt");
    readMonsters("monsters.txt");

    sorcerer_anger_ = 0;

    num_monsters_defeated_ = 0;

    num_explored_spaces_ = 0;

    turn_track_ = 0;

    game_over_ = false;
}

TravelingParty& Dungeon::getParty()
{
    return tp_;
}

Map& Dungeon::getMap()
{
    return map_;
}

void Dungeon::setGameOverStatus(bool game_condition)
{
    game_over_ = game_condition;
}

bool Dungeon::isGameOver() const
{
    return game_over_;
}

int Dungeon::getNumTurns() const
{
    return turn_track_;
}

int Dungeon::getMonstersDefeated() const
{
    return num_monsters_defeated_;
}

void Dungeon::readRiddles(string file_name)
{
    ifstream fin; 
    
    string riddle_line;

    string response;
    
    int split_riddle;

    // use to store riddles in a sequence
    // then use similar process as to readMonsters and create rows of riddles;
    vector<string> riddles;

    fin.open(file_name);

    if(fin.fail())
    {
        cout << "There are no riddles to solve today." << endl;
        return;
    }

    while(getline(fin, riddle_line))
    {
        string temp_arr[2];

        split_riddle = split(riddle_line, '~', temp_arr, 2);

        riddles.push_back(temp_arr[0]); // question
        riddles.push_back(temp_arr[1]); // answer

    }

    fin.close();

    int count = 0;

    for(int i = 0; i < 20; i++)
    {
        vector<string> row_holder;
        for(int j = 0; j < 2; j++)
        {
            row_holder.push_back(riddles[count]);
            count++;
        }
        riddles_.push_back(row_holder);
    }
}

void Dungeon::readMonsters(string file_name)
{
    ifstream fin;

    string read_line;

    vector<Monster> temp_monster_store;

        int splits = 0;

        fin.open(file_name);

        if (fin.fail())
        {
            cout << "You get off lucky, all the monster are hibernating." << endl;
            return;
        }

        while(getline(fin, read_line))
        {
            string line_monster[2];
            splits = split(read_line, ',', line_monster, 2);

            temp_monster_store.push_back(Monster(line_monster[0], stoi(line_monster[1])));

        }

        int count = 0;

        for(int i = 0; i < 5; i++) // number of rows I want
        {
            vector<Monster> temp;
            for(int j = 0; j < 4; j++) // size of columns per row
            {
                temp.push_back(temp_monster_store[count]);
                count++;
            }
            monsters_.push_back(temp);
            
        }
        vector<Monster> sorcerer = {temp_monster_store[temp_monster_store.size() - 1]};
        monsters_.push_back(sorcerer);
}

vector<Monster> Dungeon::returnMonsterRow(int row)
{
    return monsters_[row];
}

vector<string>& Dungeon::returnRiddleRow(int row)
{
    return riddles_[row];
}

void Dungeon::removeRiddle(int row, int col)
{
    riddles_[row].erase(riddles_[row].begin() + col);
}

bool Dungeon::doorPuzzle()
{
    // return false signifies player failed to beat door
    // return true means player won

    cout << "To open this door without a key, you must beat the door in a game of Boulder, Parchment, Shears." << endl;
    cout << "You have three attempts to beat the door, before something horrible happens." << endl;


    int door_choice = 0;
    int player_choice = 0;

    int unbeaten_count = 0;

    for(int i = 0; i < 3; i++)
    {
        do 
        {
            do
            {
                cout << "Please make a choice:" << endl;
                cout << "1. Boulder" << endl;
                cout << "2. Parchment" << endl;
                cout << "3. Shears" << endl;
                cin >> player_choice;
            } while(player_choice < 1 || player_choice > 3);

            door_choice = (rand() % 3) + 1; // 1 - 3;

            if(player_choice == door_choice)
            {
                cout << "It's a tie! Select again." << endl;
            }

        } while(player_choice == door_choice);

        if(player_choice == 1 && door_choice == 3)
        {
            cout << "Boulder beats Shears, you can enter the room!" << endl;
            return true;
        }
        else if(player_choice == 2 && door_choice == 1)
        {
            cout << "Parchment beats Boulder, you can enter the room!" << endl;
            return true;
        }
        else if(player_choice == 3 && door_choice == 2)
        {
            cout << "Shears beats Parchment, you can enter the room!" << endl;
            return true;
        }
        else 
        {
            cout << "You have lost to the door! Try again!" << endl;
            unbeaten_count++;
        }

    }

    if(unbeaten_count == 3)
    {
        cout << "You were unable to beat the door within 3 tries. A player must die!" << endl;

        int rand_player_death = (rand() % tp_.getPlayerList().size() - 1) + 1;

        tp_.removePlayer(rand_player_death); 

        return false;
    }

    return false;


}
/*
- unsure how to implement game end
- wondering if I should just make it a bool
- or if I should just create a data member which is either true when the game should end
- or false when the game is not over
- I think a mix of both, a bool variable for the game end
- and a function which checks situations which end the game (ex: sorcerer anger level == 100);

*/
bool Dungeon::checkGameEnd()
{
    // player wins when all rooms cleared and at least on other party member proceeds to dungeon exit

    if(tp_.getNumRooms() == 5 && tp_.getPlayerList().size() > 1 && (map_.getDungeonExitRow() == map_.getPlayerRow()) && (map_.getDungeonExitCol() == map_.getPlayerCol()))
    {

        cout << "Congratulations " << tp_.getPlayerList()[0].getName() << ", you have crusaded the dungeon! Well done!" << endl;

        game_over_ = true;
        // victory for player

    }
    else if(tp_.getPlayerList().size() == 1)
    {
        // game end
        cout << "You are the last one left. You can no longer complete the dungeon and the game shall end." << endl;

        game_over_ = true;

        // print message informing player of how they lost
    }
    else if(sorcerer_anger_ == 100)
    {
        cout << "You have angered the sorcerer far too much, he is far too powerful now." << endl;
        cout << "KWFHAJIHFOUHA, your party has been completely wiped out!" << endl;

        game_over_ = true;

        for(int i = 0; i < tp_.getPlayerList().size(); i++)
        {
            tp_.removePlayer(i);
            i--;
        }

    }

    return game_over_;

    // create function here to display final stats
}

void Dungeon::takeTurn()
{
    /* Algo:
    - first line will be to get player row and player col
    - store these in int variables
    - use switch statement based on user input based on the menu based on the current player position
    - remember to calculate misfortunes
    - include the misfortune functions prewrote (misfortuneKey() and misfortuneMain())
    --- misfortune key is reserved for the instances where the player is trying to open a door using a key
    - create a door puzzle function which will be used when the player is on a room and tries to open door without key
    - add a check in the fight function which ensures that there are monsters to fight at the current challenge rating
    - moving action has a separate misfortune to be calculated
    */

    int player_row = map_.getPlayerRow();
    int player_col = map_.getPlayerCol();

    bool fight_outcome = false;

    int action = 0;
    char direction;

    bool move_result;

    int move_misfortune = 0;
    
    int break_prob = 0;

    int cook_choice = 0;

    int num_ingredients = 0;

    // when player is on normal space
   if(!map_.isRoomLocation(player_row, player_col) && !map_.isNPCLocation(player_row, player_col))
   {
        cout << "How do you want to proceed?" << endl;
        cout << "1. Move" << endl;
        cout << "2. Investigate" << endl;
        cout << "3. Pick a Fight." << endl;
        cout << "4. Cook and Eat" << endl;
        cout << "5. Give up" << endl;
        cout << "Please select the number corresponding to your desired action." << endl;

        cin >> action;

        switch(action)
        {
            case 1: // move, dont calc misfortune for this, on every other action there is a 40% chance of a misfortune
            {
                do
                {                 
                    cout << "In what direction would you like to move?" << endl;
                    cout << "w. Up" << endl;
                    cout << "a. Left" << endl;
                    cout << "s. Down" << endl;
                    cout << "d. Right" << endl;
                    cout << "Enter the character corresponding to your desired direction" << endl;

                    cin >> direction;

                } while(direction != 'w' && direction != 's' && direction != 'a' && direction != 'd');

                move_result = map_.move(direction);

                while(move_result == false)
                {
                    cout << "You cannot move in this manner. Please choose another direction." << endl;

                    do
                    {                 
                        cout << "In what direction would you like to move?" << endl;
                        cout << "w. Up" << endl;
                        cout << "a. Left" << endl;
                        cout << "s. Down" << endl;
                        cout << "d. Right" << endl;
                        cout << "Enter the character corresponding to your desired direction" << endl;

                        cin >> direction;

                    } while(direction != 'w' && direction != 's' && direction != 'a' && direction != 'd');
                    
                    move_result = map_.move(direction);
                }
                
                // calculate misfortune for each player

                for(int i = 0; i < tp_.getPlayerList().size(); i++)
                {
                    move_misfortune = rand() % 10;

                    if(move_misfortune < 2)
                    {
                        tp_.getPlayer(i).setFullness(tp_.getPlayer(i).getFullness() - 1);
                        //will need to figure out if I should have some function
                        // which is constantly checking party members fullness
                        // and how that interacts with the game ending in a turn
                    }
                }           


                if(!map_.isExplored(map_.getPlayerRow(), map_.getPlayerCol()))
                {
                    sorcerer_anger_++;
                }

                break;
            }
            case 2: // investigate
            {
                if(!map_.isExplored(player_row, player_col))
                {
                    map_.exploreSpace(player_row, player_col);

                    num_explored_spaces_++;

                    int explore = rand() % 10;

                    if(explore == 0)
                    {
                        cout << "You found a key!" << endl;

                        tp_.setNumKeys(tp_.getNumKeys() + 1);

                    }
                    else if(explore >= 1 && explore <=2) // 1 or 2
                    {
                        if(tp_.getNumRooms() == 0)
                        {
                            return;
                            // exit the function
                            // no treasure can be found until the player has cleared a room
                        }
                        cout << "You found a piece of treasure!" << endl;

                        if(tp_.getNumRooms() == 1)
                        {
                            // silver ring
                            tp_.getInventory().addTreasure(Treasure("Silver Ring", 10));
                        }
                        else if(tp_.getNumRooms() == 2)
                        {
                            //Ruby Necklace
                            tp_.getInventory().addTreasure(Treasure("Ruby Necklace", 20));
                        }
                        else if(tp_.getNumRooms() == 3)
                        {
                            // Emerald Bracelet
                            tp_.getInventory().addTreasure(Treasure("Emerald Bracelet", 30));
                        }
                        else if(tp_.getNumRooms() == 4)
                        {
                            // Diamond circlet
                            tp_.getInventory().addTreasure(Treasure("Diamond Circlet", 40));
                        }
                        else if(tp_.getNumRooms() == 5)
                        {
                            // Netherite Gobvlet
                            tp_.getInventory().addTreasure(Treasure("Netherite Goblet", 50));
                        }
                        
                    }
                    else if(explore >= 3 && explore <= 4)
                    {
                        cout << "OH NO! You must fight a monster!" << endl;

                        // call fight function
                        fight_outcome = fight(tp_.getNumRooms());
                    }

                    int fullness_drop = 0;

                    for(int i = 0; i < tp_.getPlayerList().size(); i++)
                    {
                        if(explore == 3 || explore == 4) // don't repeat for fighting monster
                        {
                            break;
                        }

                        fullness_drop = rand() % 2;

                        if(fullness_drop == 0)
                        {
                            tp_.getPlayerList()[i].setFullness(tp_.getPlayerList()[i].getFullness() - 1);
                            // do I need a check to see if the last party member died
                            // might create a function which checks the fullness levels of the party members

                        }

                    }
                    misfortuneMain();
                }
                else
                {
                    cout << "The space has already been explored, please select another option." << endl;
                    return;
                    // my thought process is that in the game driver
                    // I envision having take_turn() function running on a do while loop
                    // as long as the game has not ended
                    // so a return here would just end the current turn action
                    // and then following that, the player would just be asked the same question

                }

                break;
            }
            case 3: // fight
            {
                fight_outcome = fight(tp_.getNumRooms());

                misfortuneMain();

                break;
            }
            case 4: // cook and eat
            {
                cook_choice = 0;

                num_ingredients = 0;

                do 
                {
                    cout << "What piece of cookware would you like to use?" << endl;

                    for(int i = 0; i < tp_.getInventory().getCookwareList().size(); i++)
                    {
                        cout << i + 1 << ". " << tp_.getInventory().getCookwareList()[i].getCookName() << endl;
                    }

                    cout << "Enter the number corresponding to your cookware choice." << endl;

                    cin >> cook_choice;
                } while(cook_choice < 1 || cook_choice >= tp_.getInventory().getCookwareList().size());
                
                do
                {
                    cout << "How much ingredients would you like to cook (in increments of 5)?" << endl;
                    cin >> num_ingredients;

                } while (num_ingredients < 0 || num_ingredients > tp_.getInventory().getNumIngredients());
                            

                break_prob = rand() % 100; // 0 - 99

                if(break_prob < tp_.getInventory().getCookwareList()[cook_choice - 1].getCookBreak())
                {
                    cout << "The cook was unsuccesful! The meal was not created! The cookware and ingredients have been lost!" << endl;

                    tp_.getInventory().removeCookware(cook_choice - 1);
                    tp_.getInventory().setIngredients(tp_.getInventory().getNumIngredients() - num_ingredients);

                }
                else
                {
                    cout << "The cook was succesful! All player's fullness have been updated." << endl;

                    tp_.getInventory().setIngredients(tp_.getInventory().getNumIngredients() - num_ingredients);

                    int fullness_increase = num_ingredients / 5;

                    for(int i = 0; i < tp_.getPlayerList().size(); i++)
                    {
                        tp_.getPlayerList()[i].setFullness(tp_.getPlayerList()[i].getFullness() + fullness_increase);

                    }

                }

                misfortuneMain();

                displayStats();

                break;
            }
            case 5: // give up
            {
            // not sure how to implement this or to completely stop the game
            // might create a function for this because there are many instances where the game can end
            // also need to have a write to file component in game end function
                
                cout << "I'm sad that you feel you must quit, best of luck." << endl;

                game_over_ = true;

                break;
            }
            default:

                cout << "Please enter a valid input." << endl;
                
                break;

                
        }
   }
   else if(map_.isNPCLocation(player_row, player_col))
   {
        cout << "How do you want to proceed?" << endl;
        cout << "1. Move" << endl;
        cout << "2. Speak to NPC" << endl;
        cout << "3. Give up" << endl;
        cout << "Please select the number corresponding to your desired action." << endl;

        cin >> action;

        switch(action)
        {
            case 1: // move
            {
               do
                {                 
                    cout << "In what direction would you like to move?" << endl;
                    cout << "w. Up" << endl;
                    cout << "a. Left" << endl;
                    cout << "s. Down" << endl;
                    cout << "d. Right" << endl;
                    cout << "Enter the character corresponding to your desired direction" << endl;

                    cin >> direction;

                } while(direction != 'w' && direction != 's' && direction != 'a' && direction != 'd');

                move_result = map_.move(direction);

                while(move_result == false)
                {
                    cout << "You cannot move in this manner. Please choose another direction." << endl;

                    do
                    {                 
                        cout << "In what direction would you like to move?" << endl;
                        cout << "w. Up" << endl;
                        cout << "a. Left" << endl;
                        cout << "s. Down" << endl;
                        cout << "d. Right" << endl;
                        cout << "Enter the character corresponding to your desired direction" << endl;

                        cin >> direction;

                    } while(direction != 'w' && direction != 's' && direction != 'a' && direction != 'd');
                    
                    move_result = map_.move(direction);
                }
                
                // calculate misfortune for each player

                for(int i = 0; i < tp_.getPlayerList().size(); i++)
                {
                    move_misfortune = rand() % 10;

                    if(move_misfortune < 2)
                    {
                        tp_.getPlayer(i).setFullness(tp_.getPlayer(i).getFullness() - 1);
                        //will need to figure out if I should have some function
                        // which is constantly checking party members fullness
                        // and how that interacts with the game ending in a turn
                    }
                } 

                if(!map_.isExplored(map_.getPlayerRow(), map_.getPlayerCol()))
                {
                    sorcerer_anger_++;
                } 
                break;
            }
            case 2: // speak to npc
            {
                NPC();

                misfortuneMain();

                break;
            }
            case 3: // give up
            {
                cout << "I'm sad that you feel you must quit, best of luck." << endl;

                game_over_ = true;

                break;
            }
            default:

                cout << "Please enter a valid input." << endl;
                break;
        }
   }
   else if(map_.isRoomLocation(player_row, player_col))
   {
        cout << "How do you want to proceed?" << endl;
        cout << "1. Move" << endl;
        cout << "2. Open the Door" << endl;
        cout << "3. Give up" << endl;
        cout << "Please select the number corresponding to your desired action." << endl;
   
        cin >> action;

        switch(action)
        {
            case 1: // move
            {
                do
                {                 
                    cout << "In what direction would you like to move?" << endl;
                    cout << "w. Up" << endl;
                    cout << "a. Left" << endl;
                    cout << "s. Down" << endl;
                    cout << "d. Right" << endl;
                    cout << "Enter the character corresponding to your desired direction" << endl;

                    cin >> direction;

                } while(direction != 'w' && direction != 's' && direction != 'a' && direction != 'd');

                move_result = map_.move(direction);

                while(move_result == false)
                {
                    cout << "You cannot move in this manner. Please choose another direction." << endl;

                    do
                    {                 
                        cout << "In what direction would you like to move?" << endl;
                        cout << "w. Up" << endl;
                        cout << "a. Down" << endl;
                        cout << "s. Left" << endl;
                        cout << "d. Right" << endl;
                        cout << "Enter the character corresponding to your desired direction" << endl;

                        cin >> direction;

                    } while(direction != 'w' && direction != 's' && direction != 'a' && direction != 'd');
                    
                    move_result = map_.move(direction);
                }
                
                // calculate misfortune for each player

                for(int i = 0; i < tp_.getPlayerList().size(); i++)
                {
                    move_misfortune = rand() % 10;

                    if(move_misfortune < 2)
                    {
                        tp_.getPlayer(i).setFullness(tp_.getPlayer(i).getFullness() - 1);
                        //will need to figure out if I should have some function
                        // which is constantly checking party members fullness
                        // and how that interacts with the game ending in a turn
                    }
                }

                if(!map_.isExplored(map_.getPlayerRow(), map_.getPlayerCol()))
                {
                    sorcerer_anger_++;
                }
                break;
            }
            case 2: // open door
            {
            // involes fight()
            // I think I will change fight to return a boolean on the outcome of the fight
            // true will equate to a party win
            // false equates to a party loss
            // will use this in a conditional based on github instructions

            if(tp_.getNumKeys() == 0)
            {
                cout << "You have fallen into a trap! You must solve a puzzle to get out!" << endl;

                bool door = doorPuzzle();

                if(door == true)
                {
                    fight_outcome = fight(tp_.getNumRooms() + 1);

                    if(fight_outcome == true)
                    {
                        misfortuneKey();

                        map_.removeRoom(player_row, player_col); 
                        // make sure that player_row and _col are being updated

                        tp_.setNumRooms(tp_.getNumRooms() + 1);

                        num_explored_spaces_++;
                    }
                }
            }
            else if(tp_.getNumKeys() > 0)
            {
                cout << "The key has unlocked the door, and has revealed a monster." << endl;
                cout << "It's time to duel!" << endl;

                tp_.setNumKeys(tp_.getNumKeys() - 1);

                fight_outcome = fight(tp_.getNumRooms() + 1);

                if(fight_outcome == true)
                {
                    // check if the fight function has cout statements saying how the fight went

                    // call misfortune function - 60 percent chance;
                    misfortuneKey();

                    map_.removeRoom(player_row, player_col); 
                    // make sure that player_row and _col are being updated

                    tp_.setNumRooms(tp_.getNumRooms() + 1);

                    num_explored_spaces_++;
                }
                else if (fight_outcome == false)
                {
                    // key is lost
                    // room not changed to clear
                    // 40 percent misfortune chance
                    // 

                    misfortuneMain();

                    tp_.setNumKeys(tp_.getNumKeys() - 1);
                }
            }
                break;
            }
            case 3: // give up
            {
                cout << "I'm sad that you feel you must quit, best of luck." << endl;

                game_over_ = true;


                break;
            }
            default:

                cout << "Please enter a valid input." << endl;
                break;
        }
   }

    turn_track_++;

}

void Dungeon::mapGeneration()
{
    // seed rand using time function
    // from there just call rand() and based on its ouput determine positions
    srand(time(0));

    map_.setPlayerPosition(0, 0); // setting player position firsts
    
    int exit_column = (rand() % 12);

    map_.setDungeonExit(11, exit_column); // setting exit position next so that rooms can exist on back row

    int room_store[5][2]; // columns store row, column | each row a new room 
    int NPC_store[5][2]; 
    // randomly generating room positions
    for(int r = 0; r < 5; r++)
    {
        do
        {
            for(int c = 0; c < 2; c++)
            {
                if(c % 2 == 0) // setting row position of room
                {
                    room_store[r][c] = (rand() % 12); // not placing any rooms on last row
                }
                else if(c % 2 == 1)
                {
                    room_store[r][c] = (rand() % 12); // setting column position of room
                }
            }
        }while(!map_.isFreeSpace(room_store[r][0], room_store[r][1]));

        map_.addRoom(room_store[r][0], room_store[r][1]);
    }

    for(int k = 0; k < 5; k++)
    {
        do
        {
            for(int i = 0; i < 2; i++)
            {
                if(i % 2 == 0) // setting row position of room
                {
                    NPC_store[k][i] = (rand() % 12); // not placing any rooms on last row
                }
                else if(i % 2 == 1)
                {
                    NPC_store[k][i] = (rand() % 12); // setting column position of room
                }
            }
        }while(!map_.isFreeSpace(NPC_store[k][0], NPC_store[k][1]));

        map_.addNPC(NPC_store[k][0], NPC_store[k][1]);
    }

   // map_.displayMap();
}

void Dungeon::displayStats()
{
    cout << "+-------------+" << endl;
    cout << "| STATUS      |" << endl;
    cout << "| Rooms Cleared: " << tp_.getNumRooms() << " | Keys: " << tp_.getNumKeys() << " | Anger Level: " << sorcerer_anger_ << endl;
    // create an inventory function to print this, allows me to use it later for merchant function
    tp_.getInventory().inventoryDisplay();
    cout << "| PARTY       |" << endl;
    cout << "| " << tp_.getPlayer(0).getName() << " | Fullness: " << tp_.getPlayer(0).getFullness() << endl;
    cout << "| " << tp_.getPlayer(1).getName() << " | Fullness: " << tp_.getPlayer(1).getFullness() << endl;
    cout << "| " << tp_.getPlayer(2).getName() << " | Fullness: " << tp_.getPlayer(2).getFullness() << endl;
    cout << "| " << tp_.getPlayer(3).getName() << " | Fullness: " << tp_.getPlayer(3).getFullness() << endl;
    cout << "| " << tp_.getPlayer(4).getName() << " | Fullness: " << tp_.getPlayer(4).getFullness() << endl;
    cout << "+-------------+" << endl;
}

void Dungeon::displayFinalStats()
{
    ofstream fout;

    fout.open("results.txt");

    if(fout.fail())
    {
        cout << "No stats to display." << endl;
        return;
    }

    fout << "Surviving party members:" << endl;

    for(int i = 0; i < tp_.getPlayerList().size(); i++)
    {
        fout << tp_.getPlayer(i).getName() << endl;
    }

    fout << "Number of rooms cleared:" << endl;
    fout << tp_.getNumRooms() << endl;

    fout << "Gold pieces remaining:" << endl;
    fout << tp_.getInventory().getNumGold() << endl;

    fout << "Remaining treasure in inventory:" << endl;

    for(int j = 0; j < tp_.getInventory().getTreasureList().size(); j++)
    {
        fout << tp_.getInventory().getTreasureList()[j].getTreasureName();
        fout << " | " << tp_.getInventory().getTreasureList()[j].getTreasurePrice() << endl;

    }

    fout << "Number of explored spaces:" << endl;
    fout << num_explored_spaces_ << endl;

    fout << "Number of monsters defeated:" << endl;
    fout << num_monsters_defeated_ << endl;

    fout << "Number of turns elapsed:" << endl;
    fout << turn_track_ << endl;

    fout << "You made it!" << endl; 
}

void Dungeon::removeMonster(int row, int col)
{
    if(monsters_[row].size() == 0)
    {
        cout << "There are no more monsters for you to fight at your current level." << endl;
        return;
    }

    monsters_[row].erase(monsters_[row].begin() + col);
}

void Dungeon::misfortuneKey() // only for door case in take turn
{
    // I will use two misfortune functions, one for when player tries to open door with key, and one for rest
    // only call this function after a player has tried to open a door with a key
    int misfortune_chance = rand() % 10; // 0 - 9

    if(misfortune_chance <= 5)
    {
        cout << "Tough luck, you are struck with a misfortune." << endl;

        int misfortune_prob = rand() % 10; // 0 - 9

        if(misfortune_prob <= 2)
        {
            cout << "You have been robbed." << endl;

            int rob_select = rand() % 3; // 0 - 2

            if(rob_select == 0)
            {  
                cout << "You lost 10 kg of ingredients!" << endl;
                tp_.getInventory().setIngredients(tp_.getInventory().getNumIngredients() - 10);
                 // add a condition in the setter which doesn't allow the value to be negative
            }
            else if (rob_select == 1)
            {
                int rob_cookware = rand() % tp_.getInventory().getCookwareList().size();

                cout << "You lost 1 " << tp_.getInventory().getCookwareList()[rob_cookware].getCookName() << "!" << endl;

                tp_.getInventory().removeCookware(rob_cookware);

            }
            else if(rob_select == 2)
            {
                cout << "You have lost a piece of armor!" << endl;
                tp_.getInventory().setArmor(tp_.getInventory().getNumArmor() - 1);

            }
            

        }
        else if (misfortune_prob == 3)
        {
            int break_weapon = rand() % tp_.getInventory().getWeaponList().size();

            cout << "OH NO! Your " << tp_.getInventory().getWeaponList()[break_weapon].getWeaponName() << " broke!" << endl;
        }
        else if(misfortune_prob > 3 && misfortune_prob <= 6)
        {
            int player_poisoning = (rand() % (tp_.getPlayerList().size() - 1)) + 1;
        
            tp_.getPlayerList()[player_poisoning].setFullness(tp_.getPlayerList()[player_poisoning].getFullness() - 10);

            if (tp_.getPlayerList()[player_poisoning].getFullness() == 0)
            {
                cout << tp_.getPlayerList()[player_poisoning].getName() << " has died of hunger." << endl;   

                // repeat code from fight (if conditionals removing weapons)

            }
            else
            {
                cout << tp_.getPlayerList()[player_poisoning].getName() << "'s fullness has dropped by 10 points" << endl;
            }
        }
        else if(misfortune_prob > 6)
        {
            // team member locked in room

            int party_lock = ((rand() % tp_.getPlayerList().size() - 1) + 1);

            cout << "OH NO! Your teammate " << tp_.getPlayerList()[party_lock].getName() << " is trapped in the previous room and is unable to ge through. You must continue without them." << endl;

            tp_.removePlayer(party_lock);

            if(tp_.getPlayerList().size() == 1)
            {
                // code for game end, or function for game end, regardless, game ends
            }
            else 
            {
                cout << "Your party size has reduced to " << tp_.getPlayerList().size() << " members." << endl;
            }
        }
    }
    else
    {
        cout << "You get off lucky this time." << endl;
        return;
    }
}

void Dungeon::misfortuneMain()
{
    // main misfortune function that will be used throughout the game
     int misfortune_chance = rand() % 10; // 0 - 9

    if(misfortune_chance <= 3)
    {
        cout << "Tough luck, you are struck with a misfortune." << endl;

        int misfortune_prob = rand() % 10; // 0 - 9

        if(misfortune_prob <= 2)
        {
            cout << "You have been robbed." << endl;

            int rob_select = rand() % 3; // 0 - 2

            if(rob_select == 0)
            {  
                cout << "You lost 10 kg of ingredients!" << endl;
                tp_.getInventory().setIngredients(tp_.getInventory().getNumIngredients() - 10);
                 // add a condition in the setter which doesn't allow the value to be negative
            }
            else if (rob_select == 1)
            {
                int rob_cookware = rand() % tp_.getInventory().getCookwareList().size();

                cout << "You lost 1 " << tp_.getInventory().getCookwareList()[rob_cookware].getCookName() << "!" << endl;

                tp_.getInventory().removeCookware(rob_cookware);

            }
            else if(rob_select == 2)
            {
                cout << "You have lost a piece of armor!" << endl;
                tp_.getInventory().setArmor(tp_.getInventory().getNumArmor() - 1);

            }
            

        }
        else if (misfortune_prob == 3)
        {
            int break_weapon = rand() % tp_.getInventory().getWeaponList().size();

            cout << "OH NO! Your " << tp_.getInventory().getWeaponList()[break_weapon].getWeaponName() << " broke!" << endl;
        }
        else if(misfortune_prob > 3 && misfortune_prob <= 6)
        {
            int player_poisoning = (rand() % (tp_.getPlayerList().size() - 1)) + 1;
        
            tp_.getPlayerList()[player_poisoning].setFullness(tp_.getPlayerList()[player_poisoning].getFullness() - 10);

            if (tp_.getPlayerList()[player_poisoning].getFullness() == 0)
            {
                cout << tp_.getPlayerList()[player_poisoning].getName() << " has died of hunger." << endl;   

                // repeat code from fight (if conditionals removing weapons)

            }
            else
            {
                cout << tp_.getPlayerList()[player_poisoning].getName() << "'s fullness has dropped by 10 points" << endl;
            }
        }
    }
    else
    {
        cout << "You get off lucky this time." << endl;
        return;
    }
}

void Dungeon::NPC()
{
    /* thought process:
    - read a text file which has the riddle and then the answer separated by a ~ (alter the text file to be this way)
    - store the puzzles and answer in a vector, the even index will be the riddle, the odd index is the riddles answer
    - need to update the split function to take vector as an input parameter, and have to alter function to use vector methods
    - First ask the player to solve a puzzle
    - if the player solves the puzzle, ask them if they want to barter for some goods
    - if the player says yes, open the merchant menu
    - otherwise, the NPC will summon a monster to be fought, call fight() function - yet to be implemented
    - regardless, remove the NPC from the board, update the space as explored (interact with the map data member in the class)
    - need to read from the file but also write to it (overwrite existing information excluding the solved riddle)
    */

    string response;

    char merchant_confirmation;

    // need to choose a random number between 0 and 19

    // the arithmetic is to generate a positive random number which is even from [0, riddles.size() -1]
    int riddle_index = rand() % riddles_.size();
    // this should eliminate the need to check whether the riddle index is even or odd, and thus riddle_index should always be on the riddle question and never the answer

    cout << "It is time for you to solve a riddle." << endl;

    cout << riddles_[riddle_index][0] << endl;

    cout << "What is the answer to this riddle?" << endl;
    cin >> response;

    if(response == riddles_[riddle_index][1])
    {
        cout << "Correct! I'm glad to part ways with some items for a fair price, would you like to make a purchase? (y/n)" << endl;
        cin >> merchant_confirmation;

        if(merchant_confirmation == 'y')
        {
            visitMerchant(tp_.getNumRooms());
        }
        else 
        {
            cout << "No worries, stay safe on your journey!" << endl;
            return;
        }

    }
    else
    {
        cout << "Fool, that is incorrect. It's time to duel!" << endl;
        fight(tp_.getNumRooms()); // call fight function which should handle fight sequence and random selection of monster
    }

       
    //regardless of outcome of puzzle, remove npc, mark space as explored, and rewrite over the riddles text without the riddle that was asked

    // done overwriting the riddles text to not include the riddle that was already given
    // no longer need to overwrite file if I implement a read riddles function and a function to remove the riddle

    // now need to change the NPC space: remove npc from the map and then mark it as explored

    map_.removeNPC(map_.getPlayerRow(), map_.getPlayerCol());
    num_explored_spaces_++;
    // by removing the NPC, the map space should be marked as explored, no more code needed

    



}

bool Dungeon::fight(int num_rooms)
{
    /* Notes / algorithm
    - First read through the monsters.txt file and use random numbers to randomly select a monster based on the number of rooms the party has cleared
    - print a message saying which monster they will fight
        - maybe initialize a monster object based on the process of reading through the file and selecting the monster
    - check the number of weapons the party has
        - if the party has 0 weapons, only have option to surrender
        - if party has at least one weapon they have both option to fight and to surrender
    - offer them the option based on conditional
    - if they choose to attack
        - calculate the party weapon strength
        - calculate fight outcome
            - for value d (different weapons) use nested loop structure to check if each weapon is different
            - outer loop is the name being compared to the rest of the weapons
            - inner loop iterates the item being compared
            - get numnber of armor sets
            - get challenge rating
            - create two different random numbers 1-6
        - if result is greater than 0, party wins
        - if result less than or equal to 0, party loses
            - then more conditionals based on fight outcome
            - all within if conditional if they choose to fight
    */

    //going to simplify structure by only reading from the file a single time at the beginning of the game, might do something similar with the riddles as well
    // this will make it easier because the contents of the file are only at a constant once, from there can use functions like remove monster to remove 
    // might make monsters data member a 2d vector where each row is a set of monsters of a specific challenge rating

    if(monsters_[num_rooms].size() == 0)
    {
        cout << "There are no more monsters for you to fight at your current level." << endl;
        return true;
    }

    int r1 = (rand() % 6) + 1;
    int r2 = (rand() % 6) + 1;

    int a = tp_.getInventory().getNumArmor();
    // use to store challenge rating of selected monster
    
    bool unique_weapon_list = true;

    int random_monster_selection = rand() % monsters_[num_rooms].size(); // will store the index which belongs to the monster which will be selected
    // monster will be located at , [num_rooms_, random_monster_selection];
    // going to have a 2d vector as a data member in dungeon class

    cout << monsters_[num_rooms][random_monster_selection].getName() << " AHEAD! THEY LOOK HOSTILE!" << endl;

    if(tp_.getInventory().getWeaponList().size() >= 1 && a > 0)
    {
        int fight_decision = 0;
        
        cout << "What would you like to do?" << endl;
        cout << "1. Fight!" << endl;
        cout << "2. Surrender!" << endl;
        cin >> fight_decision;

        while(fight_decision != 1 && fight_decision != 2)
        {
            cout << "That is not an option! You can either: " << endl;
            cout << "1. Fight!" << endl;
            cout << "2. Surrender!" << endl;
            cin >> fight_decision;
        }

        if(fight_decision == 1)
        {
            // fight code, calculating battles and such
            int w = tp_.getInventory().getWeaponList().size() + (tp_.getInventory().getNumWeapon("Rapier of Ragnarok") * 1) + (tp_.getInventory().getNumWeapon("Axe of Alabasta") * 2) + (tp_.getInventory().getNumWeapon("Zoro's Longsword") * 3);
            int c = monsters_[num_rooms][random_monster_selection].getDifficulty();
            // this value (c) will also always be num rooms + 1
            int d = 0;

            for(int i = 0; i < tp_.getInventory().getWeaponList().size() - 1; i++)
            {
                for(int j = i + 1; j < tp_.getInventory().getWeaponList().size(); j++)
                {
                    if(tp_.getInventory().getWeaponList()[i].getWeaponName() == tp_.getInventory().getWeaponList()[j].getWeaponName())
                    {
                        unique_weapon_list = false;
                        break;
                    }
                }
            }
            if(unique_weapon_list == true)
            {
                d = 4;
            }

            int battle_outcome = (r1 * w + d) - ((r2 * c) / a);

            if(battle_outcome > 0)
            {
                tp_.getInventory().setGold(tp_.getInventory().getNumGold() + (10 * c));
                tp_.getInventory().setIngredients(tp_.getInventory().getNumIngredients() + (5 * c));

                int key_drop = rand() % 10;

                if(key_drop == 0)
                {
                    tp_.setNumKeys(tp_.getNumKeys() + 1);
                }

                removeMonster(num_rooms, random_monster_selection);
                // create remove monster function;
                // first parameter: int rows
                // second parameter: int columns
                num_monsters_defeated_++;

                return true; // outcome of fight
                
            }
            else if(battle_outcome <= 0)
            {
                cout << "Today, you and your party was not strong enough. You have been defeated!" << endl;

                // losing gold
                tp_.getInventory().setGold(tp_.getInventory().getNumGold() - (tp_.getInventory().getNumGold() / 4));

                tp_.getInventory().setIngredients(tp_.getInventory().getNumIngredients() - (5 * c));
            
                for(int i = tp_.getPlayerList().size() - 1; i >= 1; i--)
                {
                    if(tp_.getInventory().getNumArmor() > i)
                    {
                        int slay_calc = rand() % 100; // 0 - 99

                        if(slay_calc < 5)
                        {
                            cout << tp_.getPlayer(i).getName() << " has been slain to the monster." << endl;

                            // removing weapons and other items from inventory;
                            if(tp_.getPlayerList().size() == tp_.getInventory().getCookwareList().size())
                            {
                                tp_.getInventory().removeCookware(i);
                            }
                            if(tp_.getPlayerList().size() == tp_.getInventory().getWeaponList().size())
                            {
                                tp_.getInventory().removeWeapon(i);

                            }   
                            if(tp_.getPlayerList().size() == tp_.getInventory().getTreasureList().size())
                            {
                                tp_.getInventory().removeTreasure(i);
                            }
                            if(tp_.getPlayerList().size() == tp_.getInventory().getNumArmor())
                            {
                                tp_.getInventory().setArmor(tp_.getInventory().getNumArmor() - 1);
                            }

                            tp_.removePlayer(i);
                        }
                        else if (tp_.getInventory().getNumArmor() <= i)
                        {
                            int calc_death = rand() % 100; // 0 - 99

                            if(calc_death <= 9)
                            {
                                cout << tp_.getPlayer(i).getName() << " has been slain to the monster." << endl;

                                // removing weapons and other items from inventory;
                                if(tp_.getPlayerList().size() == tp_.getInventory().getCookwareList().size())
                                {
                                    tp_.getInventory().removeCookware(i);
                                }
                                if(tp_.getPlayerList().size() == tp_.getInventory().getWeaponList().size())
                                {
                                    tp_.getInventory().removeWeapon(i);

                                }   
                                if(tp_.getPlayerList().size() == tp_.getInventory().getTreasureList().size())
                                {
                                    tp_.getInventory().removeTreasure(i);
                                }
                                if(tp_.getPlayerList().size() == tp_.getInventory().getNumArmor())
                                {
                                    tp_.getInventory().setArmor(tp_.getInventory().getNumArmor() - 1);
                                }   

                                tp_.removePlayer(i);  
                            }
                        }
                    }
                } 
                return false; // party did not win
            }
        }
        else if (fight_decision == 2)
        {
            // surrender code, calculating misfortunes and such
            // duplicate surrender code
            cout << "You have nothing to fight with, you must surrender!" << endl;
            cout << "Unfortunately, this means one player must be sacrificed to appease the monster." << endl;

            if(tp_.getPlayerList().size() == tp_.getInventory().getCookwareList().size())
            {
                tp_.getInventory().removeCookware(tp_.getInventory().getCookwareList().size() - 1);
            }
            if(tp_.getPlayerList().size() == tp_.getInventory().getWeaponList().size())
            {
                tp_.getInventory().removeWeapon(tp_.getInventory().getWeaponList().size() - 1);

            }   
            if(tp_.getPlayerList().size() == tp_.getInventory().getTreasureList().size())
            {
                tp_.getInventory().removeTreasure(tp_.getInventory().getTreasureList().size() - 1);
            }
            if(tp_.getInventory().getNumArmor() == tp_.getPlayerList().size())
            {
                tp_.getInventory().setArmor(tp_.getInventory().getNumArmor() - 1);
            }

            tp_.removePlayer(tp_.getPlayerList().size()-1); // add a messgae within remove player which states that a player has been removed, an then print updated party
    
        // removing the last cookware weapon

            int fullness_prob = 0;
            int player_fullness = 0;

            for(int i = 0; i < tp_.getPlayerList().size(); i++)
            {
                fullness_prob = rand() % 2;

                if(fullness_prob == 1)
                {
                    player_fullness = tp_.getPlayerList()[i].getFullness();
                    tp_.getPlayerList()[i].setFullness(player_fullness - 1);

                    cout << tp_.getPlayerList()[i].getName() << "'s fullness has been reduced by one point!" << endl;

                }
            }
            return false; // party surrendered
        }
        
    }
    else if(tp_.getInventory().getWeaponList().size() == 0 || a == 0)
    {
        // duplicate surrender code
        cout << "You have nothing to fight with, you must surrender!" << endl;
        cout << "Unfortunately, this means one player must be sacrificed to appease the monster." << endl;

        if(tp_.getPlayerList().size() == tp_.getInventory().getCookwareList().size())
        {
            tp_.getInventory().removeCookware(tp_.getInventory().getCookwareList().size() - 1);
        }
        if(tp_.getPlayerList().size() == tp_.getInventory().getWeaponList().size())
        {
            tp_.getInventory().removeWeapon(tp_.getInventory().getWeaponList().size() - 1);

        }
        if(tp_.getPlayerList().size() == tp_.getInventory().getTreasureList().size())
        {
            tp_.getInventory().removeTreasure(tp_.getInventory().getTreasureList().size() - 1);
        }
        if(tp_.getInventory().getNumArmor() == tp_.getPlayerList().size())
        {
            tp_.getInventory().setArmor(tp_.getInventory().getNumArmor() - 1);
        }

        tp_.removePlayer(tp_.getPlayerList().size()-1); // add a messgae within remove player which states that a player has been removed, an then print updated party
    
        // removing the last cookware weapon

        int fullness_prob = 0;
        int player_fullness = 0;

        for(int i = 0; i < tp_.getPlayerList().size(); i++)
        {
            fullness_prob = rand() % 2;

            if(fullness_prob == 1)
            {
                player_fullness = tp_.getPlayerList()[i].getFullness();
                tp_.getPlayerList()[i].setFullness(player_fullness - 1);

                cout << tp_.getPlayerList()[i].getName() << "'s fullness has been reduced by one point!" << endl;

            }
        }
        return false;
    }
    return false;
}

void Dungeon::visitMerchant(int num_rooms)
{

    // for the initial statement, may just display this at the beginning
    // but if I do include a take_turn data member to track the number of turns taken
    // i'll display this segment only while the take_turn data member is at 0
    /*
    Between the 5 of you, you have 100 gold pieces. 
    You will need to spend the some of your money on the following items:

    - INGREDIENTS. To make food, you have to cook raw ingredients.
    - COOKWARE. If you want to cook, you have to have cookware first.
    - WEAPONS. You'll want at least one weapon per party member to fend off monsters.
    - ARMOR. Armor increases the chances of surviving a monster attack.

    You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way. But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price...
    */
    /* Algo
    - Print merchant pickup line
    - display inventory using inventory function
    - cout choose one of the following (essentially display menu)
    - take user input
    - run switch statement based on user input
    - have switch statement, inventory printing running on do while loop
    - equation for price increase: price = int(price + (price (num_rooms * .25)));
    - Instead of having getNumItem function, could I use the merchant menu to update the number of items for each
    */

cout << "If you're looking to get supplies, you've come to the right place." << endl; 
cout << "I would be happy to part with some of my wares...for the proper price!" << endl;

int player_choice = 0;

do
{

    tp_.getInventory().inventoryDisplay();

    

    cout << "Choose one of the following:" << endl;
    cout << "1. Ingredients: To make food, you have to cook raw ingredients." << endl;
    cout << "2. Cookware: You will need something to cook those ingredients." << endl;
    cout << "3. Weapons: It's dangerous to go alone, take this!" << endl;
    cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
    cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
    cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
    cin >> player_choice;

    int total_cost = 0;
    int current_gold = tp_.getInventory().getNumGold();

    switch(player_choice)
    {
        case 1: // ingredients
        {
            int ingredient_amount = 0;

            cout << "How many kg of ingredients do you need [1 Gold / kg]? (Enter a positive multiple of 5, or 0 to cancel)" << endl;
            cin >> ingredient_amount;
        
            while(int(ingredient_amount + (ingredient_amount * (.25 * num_rooms))) > tp_.getInventory().getNumGold())
            {
                cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                
                cout << "How many kg of ingredients do you need [1 Gold / kg]? (Enter a positive multiple of 5, or 0 to cancel)" << endl;
                cin >> ingredient_amount;
            }


            char ingredient_confirmation;

            cout << "You want to buy " << ingredient_amount << " kg of ingredients for " << int(ingredient_amount + (ingredient_amount * (num_rooms * .25))) << " Gold? (y/n)" << endl;
            cin >> ingredient_confirmation;

            if(ingredient_confirmation == 'y')
            {
                tp_.getInventory().setIngredients(ingredient_amount);

                total_cost += int(ingredient_amount + (ingredient_amount * (num_rooms * .25)));

                current_gold = current_gold - total_cost;

                tp_.getInventory().setGold(current_gold);

                cout << "The current total cost is: " << total_cost << endl;

                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                continue;
            }
            else
            {
                continue;
            }
         

            break;
        }
        case 2: //cookware
        {
            cout << "I have a several types of cookware, which one would you like?" << endl;
            cout << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;

            int cook_choice = 0;

            cout << "Choose one of the following: " << endl;
            cout << "1. (25%) Ceramic Pot [" << int(2 + (2 * (.25 * num_rooms))) << " Gold]" << endl;
            cout << "2. (10%) Frying Pan [" << int(10 + (10 * (.25 * num_rooms))) << " Gold]" << endl;
            cout << "3. ( 2%) Cauldron [" << int(20 + (20 * (.25 * num_rooms))) << " Gold]" << endl;
            cout << "4. Cancel" << endl;
            cin >> cook_choice;

            int cook_amount = 0;

            cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
            cin >> cook_amount;

            char cook_confirmation;

            if(cook_amount == 0)
            {
                break;
            }
            else if(cook_choice == 1)
            {

                while(int(cook_amount * (2 + (2 * (.25 * num_rooms)))) > tp_.getInventory().getNumGold())
                {
                    cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                    cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                    cin >> cook_amount;
                }

                cout << "You want to buy " << cook_amount << " Ceramic Pot(s) for " << int(cook_amount * (2 + (2 * (.25 * num_rooms)))) << " Gold? (y/n)" << endl;
                cin >> cook_confirmation;

                if(cook_confirmation == 'y')
                {

                    for(int i = 0; i < cook_amount; i++)
                    {
                        if(tp_.getInventory().getCookwareList().size() == 5)
                        {
                            cout << "The inventory can store no more cookware." << endl;
                            continue;
                        }
                        tp_.getInventory().addCookware(Cookware("Ceramic Pot", int(cook_amount * (2 + (2 * (.25 * num_rooms)))), 25));

                    }

                    total_cost += int(cook_amount * (2 + (2 * (.25 * num_rooms))));

                    current_gold -= total_cost;

                    tp_.getInventory().setGold(current_gold);

                    cout << "The current total cost is: " << total_cost << endl;

                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    continue;
                }
                else
                {
                    cout << "Selection has been canceled." << endl;
                    continue;
                }
                
            }
            else if(cook_choice == 2)
            {
                while(int(cook_amount * (10 + (10 * (.25 * num_rooms)))) > tp_.getInventory().getNumGold())
                {
                    cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                    cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                    cin >> cook_amount;
                }

                cout << "You want to buy " << cook_amount << " Frying Pan(s) for " << int(cook_amount * (10 + (10 * (.25 * num_rooms)))) << " Gold? (y/n)" << endl;
                cin >> cook_confirmation;

                if(cook_confirmation == 'y')
                {
                    for(int i = 0; i < cook_amount; i++)
                    {
                        if(tp_.getInventory().getCookwareList().size() == 5)
                        {
                            cout << "The inventory can store no more cookware." << endl;
                            continue;
                        }
                        tp_.getInventory().addCookware(Cookware("Frying Pan", int(cook_amount * (10 + (10 * (.25 * num_rooms)))), 25));
                        
                    }

                    total_cost += int(cook_amount * (10 + (10 * (.25 * num_rooms))));

                    current_gold -= total_cost;

                    tp_.getInventory().setGold(current_gold);

                    cout << "The current total cost is: " << total_cost << endl;

                    cout << "Thank you for your patronage! What else can I get for you?" << endl; 
                    continue;
                }
                else
                {
                    continue;
                }
            }
            else if(cook_choice == 3)
            {
                while(int(cook_amount * (20 + (20 * (.25 * num_rooms)))) > tp_.getInventory().getNumGold())
                {
                    cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                    cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                    cin >> cook_amount;
                }

                cout << "You want to buy " << cook_amount << " Cauldron(s) for " << int(cook_amount * (20 + (20 * (.25 * num_rooms)))) << " Gold? (y/n)" << endl;
                cin >> cook_confirmation;

                if(cook_confirmation == 'y')
                {
                    for(int i = 0; i < cook_amount; i++)
                    {
                        if(tp_.getInventory().getCookwareList().size() == 5)
                        {
                            cout << "The inventory can store no more cookware." << endl;
                            continue;
                        }
                        tp_.getInventory().addCookware(Cookware("Cauldron", int(cook_amount * (20 + (20 * (.25 * num_rooms)))), 2));
                    }

                    total_cost += int(cook_amount * (20 + (20 * (.25 * num_rooms))));

                    current_gold -= total_cost;

                    tp_.getInventory().setGold(current_gold);

                    cout << "The current total cost is: " << total_cost << endl; 

                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    continue;
                }
                else 
                {
                    cout << "Selection has been canceled." << endl;
                    continue;
                }
                
            }

            break;
        }
        case 3: // weapons
        {
        cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl;
        cout << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;

        int weapon_choice = 0;
        
        cout << "Choose one of the following:" << endl; // need to change menu to fit the weapons I chose
        cout << "1. Club of Christ [" << int(2 + (2 * (.25 * num_rooms))) << " Gold]" << endl;
        cout << "2. Spear of Truth [" << int(2 + (2 * (.25 * num_rooms))) << " Gold]" << endl;
        cout << "3. (+1) Rapier of Ragnarok [" << int(5 + (5 * (.25 * num_rooms))) << " Gold]" << endl;
        cout << "4. (+2) Axe of Alabasta [" << int(15 + (15 * (.25 * num_rooms))) << " Gold]" << endl;
        cout << "5. (+3) Zoro's Longsword [" << int(50 + (50 * (.25 * num_rooms))) << " Gold]" << endl;
        cout << "6. Cancel" << endl;

        cin >> weapon_choice;

        int weapon_amount = 0;

        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;

        cin >> weapon_amount;

        if(weapon_amount == 0)
        {
            continue;
        }
        else if(weapon_choice == 1)
        {
            while(int(weapon_amount * (2 + (2 * (.25 * num_rooms)))) > tp_.getInventory().getNumGold())
            {
                cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                cin >> weapon_amount;
            }

            for(int i = 0; i < weapon_amount; i++)
            {
                if(tp_.getInventory().getWeaponList().size() == 5)
                {
                    cout << "The inventory can store no more weapons." << endl;
                    continue;
                }
                tp_.getInventory().addWeapon(Weapon("Club of Christ", int(2 + (2 * (.25 * num_rooms))), 0));
            }

            total_cost += int(weapon_amount * (2 + (2 * (.25 * num_rooms))));

            current_gold -= total_cost;

            tp_.getInventory().setGold(current_gold);

            cout << "The current total cost is: " << total_cost << endl; 

            cout << "Thank you for your patronage! What else can I get for you?" << endl;
            continue;
        }
        else if(weapon_choice == 2)
        {
            while(int(weapon_amount * (2 + (2 * (.25 * num_rooms)))) > tp_.getInventory().getNumGold())
            {
                cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                cin >> weapon_amount;
            }

            for(int i = 0; i < weapon_amount; i++)
            {
                if(tp_.getInventory().getWeaponList().size() == 5)
                {
                    cout << "The inventory can store no more weapons." << endl;
                    continue;
                }
                tp_.getInventory().addWeapon(Weapon("Spear of Truth", int(2 + (2 * (.25 * num_rooms))), 0));
            }

            total_cost += int(weapon_amount * (2 + (2 * (.25 * num_rooms))));

            current_gold -= total_cost;

            tp_.getInventory().setGold(current_gold);

            cout << "The current total cost is: " << total_cost << endl; 

            cout << "Thank you for your patronage! What else can I get for you?" << endl;
            continue;
        }
        else if(weapon_choice == 3)
        {
            while(int(weapon_amount * (5 + (5 * (.25 * num_rooms)))) > tp_.getInventory().getNumGold())
            {
                cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                cin >> weapon_amount;
            }

            for(int i = 0; i < weapon_amount; i++)
            {
                if(tp_.getInventory().getWeaponList().size() == 5)
                {
                    cout << "The inventory can store no more weapons." << endl;
                    continue;
                }
                tp_.getInventory().addWeapon(Weapon("Rapier of Ragnarok", int(5 + (5 * (.25 * num_rooms))), 0));
            }

            total_cost += int(weapon_amount * (5 + (5 * (.25 * num_rooms))));

            current_gold -= total_cost;

            tp_.getInventory().setGold(current_gold);

            cout << "The current total cost is: " << total_cost << endl; 

            cout << "Thank you for your patronage! What else can I get for you?" << endl;
            continue;
        }
        else if(weapon_choice == 4)
        {
            while(int(weapon_amount * (15 + (15 * (.25 * num_rooms)))) > tp_.getInventory().getNumGold())
            {
                cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                cin >> weapon_amount;
            }

            for(int i = 0; i < weapon_amount; i++)
            {
                if(tp_.getInventory().getWeaponList().size() == 5)
                {
                    cout << "The inventory can store no more weapons." << endl;
                    continue;
                }
                tp_.getInventory().addWeapon(Weapon("Axe of Alabasta", int(15 + (15 * (.25 * num_rooms))), 0));
            }

            total_cost += int(weapon_amount * (15 + (15 * (.25 * num_rooms))));

            current_gold -= total_cost;

            tp_.getInventory().setGold(current_gold);

            cout << "The current total cost is: " << total_cost << endl; 

            cout << "Thank you for your patronage! What else can I get for you?" << endl;
            continue;
        }
        else if(weapon_choice == 5)
        {
            while(int(weapon_amount * (50 + (50 * (.25 * num_rooms)))) > tp_.getInventory().getNumGold())
            {
                cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                cin >> weapon_amount;
            }

            for(int i = 0; i < weapon_amount; i++)
            {
                if(tp_.getInventory().getWeaponList().size() == 5)
                {
                    cout << "The inventory can store no more weapons." << endl;
                    continue;
                }
                tp_.getInventory().addWeapon(Weapon("Zoro's Longsword", int(50 + (50 * (.25 * num_rooms))), 0));
            }

            total_cost += int(weapon_amount * (50 + (50 * (.25 * num_rooms))));

            current_gold -= total_cost;

            tp_.getInventory().setGold(current_gold);

            cout << "The current total cost is: " << total_cost << endl; 

            cout << "Thank you for your patronage! What else can I get for you?" << endl;
            continue;
        }
        else
        {
            cout << "Selection has been canceled." << endl;
            continue;
        }
        
            break;


        }
        case 4: // armor selection
        {
            int num_suits = 0;

            cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> num_suits;

            char armor_confirmation;

            if(num_rooms == 0)
            {
                cout << "You want to buy " << num_suits << " suit(s) of armor for " << int(num_suits * 5) << " Gold? (y/n)" << endl;
                cin >> armor_confirmation;

                while(int(num_suits * 5) > tp_.getInventory().getNumGold())
                {
                    cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                    cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                    cin >> num_suits;
                }
            }
            else
            {
                cout << "You want to buy " << num_suits << " suit(s) of armor for " << int(num_suits * (5 * (.25 * num_rooms))) << " Gold? (y/n)" << endl;
                cin >> armor_confirmation;

                while(int(num_suits * (5 * (.25 * num_rooms))) > tp_.getInventory().getNumGold())
                {
                    cout << "You are currently attempting to purchase an amount for which you have insufficent funds for. Please choose another quantity of the item." << endl;
                    
                    cout << "How many would you like (Enter a positive integer, or 0 to cancel cheapskate)" << endl;
                    cin >> num_suits;
                }
            }

            if(armor_confirmation == 'y')
            {
                tp_.getInventory().setArmor(num_suits);
                
                if(num_rooms == 0)
                {
                    total_cost += int(num_suits * 5);
                }
                else
                {
                    total_cost += int(num_suits * (5 * (.25 * num_rooms)));
                }

                current_gold -= total_cost;

                tp_.getInventory().setGold(current_gold);

                cout << "The current total cost is: " << total_cost << endl; 

                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                continue;

            }
            else
            {
                continue;
            }

            break;
        }
        case 5: // selling treasures 
        {
            string treasure_choice;

            if(tp_.getInventory().getTreasureList().size() == 0)
            {
                cout << "Return back when you have something shiny for me." << endl;
                continue;
            }

            cout << "Here are the treasures you currently possess in your inventory." << endl;
            
            tp_.getInventory().printTreasureList();

            cout << "Please enter the name of the treasure you would like to sell as it appears. Enter 'Cancel' to cancel your sale." << endl;
            cin >> treasure_choice; 

            if(treasure_choice == "Silver Ring")
            {
                current_gold += 10;
                tp_.getInventory().setGold(current_gold);

                for(int i = 0; i < tp_.getInventory().getTreasureList().size(); i++)
                {
                    if(tp_.getInventory().getTreasureList()[i].getTreasureName() == "Silver Ring")
                    {
                        tp_.getInventory().removeTreasure(i);
                    }
                }

                cout << "I'll cherish this treasure like I found it me self." << endl;

                cout << "Thank you for your patronage! What else can I get for you?" << endl;
            }

            else if(treasure_choice == "Ruby Necklace")
            {
                current_gold += 20;
                tp_.getInventory().setGold(current_gold);

                for(int i = 0; i < tp_.getInventory().getTreasureList().size(); i++)
                {
                    if(tp_.getInventory().getTreasureList()[i].getTreasureName() == "Ruby Necklace")
                    {
                        tp_.getInventory().removeTreasure(i);
                    }
                }

                cout << "I'll cherish this treasure like I found it me self." << endl;

                cout << "Thank you for your patronage! What else can I get for you?" << endl;
            }
            else if(treasure_choice == "Emerald Bracelet")
            {
                current_gold += 10;
                tp_.getInventory().setGold(current_gold);

                for(int i = 0; i < tp_.getInventory().getTreasureList().size(); i++)
                {
                    if(tp_.getInventory().getTreasureList()[i].getTreasureName() == "Emerald Bracelet")
                    {
                        tp_.getInventory().removeTreasure(i);
                    }
                }

                cout << "I'll cherish this treasure like I found it me self." << endl;

                cout << "Thank you for your patronage! What else can I get for you?" << endl;
            }
            else if(treasure_choice == "Diamond Circlet")
            {
                current_gold += 10;
                tp_.getInventory().setGold(current_gold);

                for(int i = 0; i < tp_.getInventory().getTreasureList().size(); i++)
                {
                    if(tp_.getInventory().getTreasureList()[i].getTreasureName() == "Diamond Circlet")
                    {
                        tp_.getInventory().removeTreasure(i);
                    }
                }

                cout << "I'll cherish this treasure like I found it me self." << endl;

                cout << "Thank you for your patronage! What else can I get for you?" << endl;
            }
            else if(treasure_choice == "Gem-encrusted Goblet")
            {
                current_gold += 10;
                tp_.getInventory().setGold(current_gold);

                for(int i = 0; i < tp_.getInventory().getTreasureList().size(); i++)
                {
                    if(tp_.getInventory().getTreasureList()[i].getTreasureName() == "Gem-encrusted Goblet")
                    {
                        tp_.getInventory().removeTreasure(i);
                    }
                }

                cout << "I'll cherish this treasure like I found it me self." << endl;

                cout << "Thank you for your patronage! What else can I get for you?" << endl;
            }
            else if(treasure_choice == "Cancel")
            {
                cout << "No worries, come again!" << endl;
                continue;
            }
            else 
            {
                continue;
            }

            break;
        }
        case 6:
        {
            char exit_confirmation;

            cout << "Are you sure you're finished? You won't be able to buy anything else from me! (y/n)" << endl;
            cin >> exit_confirmation;

            if(exit_confirmation == 'y')
            {
                cout << "Stay safe out there! Goodbye!" << endl;
                break;
            }
            else
            {
                continue;
            }

            break;
        }
        default:

            cout << "Please enter a valid input." << endl;

            break;
    }
}while(player_choice != 6);

}
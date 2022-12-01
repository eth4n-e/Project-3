#include "Player.h"
#include <iostream>

using namespace std;

/*
  public:

        Player();
        Player(string name, int fullness);

        //getters
        string getName();
        int getFullness();

        //setters
        void setName(string name);
        void setFullness(int fullness);

};
*/

Player::Player()
{
    name_ = "";
    fullness_ = 0;
}
Player::Player(string name, int fullness)
{
    name_ = name;

    int fullness_check = fullness;

    
    while(fullness_check < 0)
    {
        cout << "Please enter a positive fullness." << endl;
        cin >> fullness_check;
    }
    
    fullness_ = fullness;
}

//getters
string Player::getName()
{
    return name_;
}

int Player::getFullness()
{
    return fullness_;
}
        //setters
void Player::setName(string name)
{
    name_ = name;
}

void Player::setFullness(int fullness)
{
    int fullness_check = fullness;

    if(fullness_check < 0)
    {
       fullness_check = 0;
    }

    if(fullness_check > 50)
    {
        fullness_check = 50;
    }

    fullness_ = fullness_check;
  
}
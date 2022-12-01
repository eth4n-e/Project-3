#include <iostream>
#include <string>

using namespace std;

#ifndef MONSTER_H
#define MONSTER_H

// within take turn function, a file will be read to initialize an array of monster objects

class Monster
{
    private:
    
    int difficulty_;
    string name_;

    public:
    
        Monster();
        Monster(string name, int difficulty);

    //getters
        int getDifficulty();
        string getName();

    //setters
        void setDifficulty(int difficulty);
        void setName(string name);
};

#endif
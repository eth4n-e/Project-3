#include "Monster.h"
#include <iostream>

using namespace std;

Monster::Monster()
{
    name_ = "";
    difficulty_ = 0;
}
Monster::Monster(string name, int difficulty)
{
    name_ = name;
    difficulty_ = difficulty;
}

    //getters
int Monster::getDifficulty()
{
    return difficulty_;
}
string Monster::getName()
{
    return name_;
}

    //setters
void Monster::setDifficulty(int difficulty)
{
    difficulty_ = difficulty;
}
void Monster::setName(string name)
{
    name_ = name;
}
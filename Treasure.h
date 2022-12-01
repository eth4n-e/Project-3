#include <iostream>

using namespace std;

#ifndef TREASURE_H
#define TREASURE_H

class Treasure
{
    private:
        int price_;
        string name_;

    public:

        //constructors
        Treasure();
        Treasure(string name, int price);

        //getters
        int getTreasurePrice() const;
        string getTreasureName() const;

        //setters
        void setTreasurePrice(int price);
        void setTreasureName(string name);



};

#endif
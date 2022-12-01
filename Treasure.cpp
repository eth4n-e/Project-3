#include "Treasure.h"

#include <iostream>

using namespace std;

Treasure::Treasure()
{
    name_ = "";
    price_ = 0;
}
Treasure::Treasure(string name, int price)
{
    name_ = name;

    int price_check = price;

    while(price_check < 0)
    {
        cout << "Please enter a positive price." << endl;
        cin >> price_check;
    }

    price_ = price_check;
}

        //getters
int Treasure::getTreasurePrice() const
{
    return price_;
}
string Treasure::getTreasureName() const
{
    return name_;
}

        //setters
void Treasure::setTreasurePrice(int price)
{
    int price_check = price;

    while(price_check < 0)
    {
        cout << "Please enter a positive price." << endl;
        cin >> price_check;
    }

    price_ = price_check;
    
}
void Treasure::setTreasureName(string name)
{
    name_ = name;
}
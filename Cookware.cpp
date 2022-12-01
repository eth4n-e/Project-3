#include "Cookware.h"
#include <iostream>

using namespace std;

Cookware::Cookware()
{
    name_ = "";
    price_ = 0;
    break_percent_ = 0;
}
Cookware::Cookware(string name, int price, int break_percent)
{
    int percent_check = break_percent;
    int price_check = price;

    // ensuring valid input for cookware
    while(percent_check < 0)
    {
        cout << "Please enter a positive percent." << endl;
        cin >> percent_check;
    }

    while(price_check < 0)
    {
        cout << "Please enter a positive price." << endl;
        cin >> price_check;
    }

    break_percent_ = percent_check;
    price_ = price_check;
    name_ = name;
}

        //getters
int Cookware::getCookBreak() const
{
    return break_percent_;
}

int Cookware::getCookPrice() const
{
    return price_;
}

string Cookware::getCookName() const
{
    return name_;
}



//setters
void Cookware::setCookBreak(int break_percent)
{
    int percent_check = break_percent;

    // ensuring valid input for cookware
    while(percent_check < 0)
    {
        cout << "Please enter a positive percent." << endl;
        cin >> percent_check;
    }

    break_percent_ = percent_check;
}

void Cookware::setCookPrice(int price)
{
    int price_check = price;

    while(price_check < 0)
    {
        cout << "Please enter a positive price." << endl;
        cin >> price_check;
    }

    price_ = price_check;
}

void Cookware::setCookName(string name)
{
    name_ = name;
}
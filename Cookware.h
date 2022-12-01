#include <iostream>

using namespace std;

#ifndef COOKWARE_H
#define COOKWARE_H

class Cookware
{
    private:
        int break_percent_;
        int price_;
        string name_;

    public:

        Cookware();
        Cookware(string name, int price, int break_percent);

        //getters
        int getCookBreak() const;
        int getCookPrice() const;
        string getCookName() const;

        //setters
        void setCookBreak(int break_percent);
        void setCookPrice(int price);
        void setCookName(string name);

};

#endif
#include "Dungeon.h"
#include "TravelingParty.h"
#include "Player.h"
#include "Item.h"
#include "Weapon.h"
#include "Cookware.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    Map map;

    Dungeon d;

    d.mapGeneration();
    
    return 0;
}
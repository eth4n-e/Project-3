#include "Monster.h"
#include "Player.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Cookware.h"
#include "Treasure.h"
#include "TravelingParty.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{

    //Player testing
    // testing player constructor
    Player p;
    p.getFullness(); // expected: 0
    p.getName(); // expected: "" (empty string)

    cout << p.getName() << endl;
    cout << p.getFullness() << endl;

    p.setFullness(50); // testing setters, initializing to standard value
    p.setName("Ethan"); // testing setter

    cout << p.getName() << endl;
    cout << p.getFullness() << endl; 

    Player parametrize_p("Jimbob", 75); // testing parametrized constructor 
    
    cout << parametrize_p.getName() << endl;
    cout << parametrize_p.getFullness() << endl; 
    // realized I should add a check to ensure fullness is only a positive integer

    cout << "-------" << endl;

    // Monster testing
    Monster m; // default object

    cout << m.getName() << endl; // empty string
    cout << m.getDifficulty() << endl; // 0 

    m.setDifficulty(4); // same with non negative check for fullness, should add conditions to make sure rating between 0 and 6;
    m.setName("Mythical Dragon");

    cout << m.getName() << endl; // Mythical dragon
    cout << m.getDifficulty() << endl; // 4

    Monster berserk("berserk", 5); // parametrized constructor

    cout << berserk.getName() << endl;
    cout << berserk.getDifficulty() << endl;

    cout << "------" << endl;

    //Testing inventory class and treasure, cookware, and weapons

    Treasure default_tester;

    cout << default_tester.getTreasureName() << endl;
    cout << default_tester.getTreasurePrice() << endl;

    default_tester.setTreasureName("Silver");
    default_tester.setTreasurePrice(40);

    cout << default_tester.getTreasureName() << endl;
    cout << default_tester.getTreasurePrice() << endl;

    Treasure tre = Treasure("Ruby", 30);

    cout << tre.getTreasureName() << endl;
    cout << tre.getTreasurePrice() << endl;

    // treasure constructors and member functions work correctly

    cout << "------" << endl;

    Weapon default_weapon;

    cout << default_weapon.getWeaponName() << endl;
    cout << default_weapon.getWeaponPrice() << endl;
    cout << default_weapon.getWeaponDamage() << endl;


    default_weapon.setWeaponName("new weapon");
    default_weapon.setWeaponPrice(20);
    default_weapon.setWeaponDamage(20);

    cout << default_weapon.getWeaponName() << endl;
    cout << default_weapon.getWeaponPrice() << endl;
    cout << default_weapon.getWeaponDamage() << endl;

    Weapon sword("longsword", 40, 10);

    cout << sword.getWeaponName() << endl;
    cout << sword.getWeaponPrice() << endl;
    cout << sword.getWeaponDamage() << endl;

    //weapon constructors, getters, setters work

    cout << "------" << endl;

    Cookware new_cookware;

    cout << new_cookware.getCookName() << endl;
    cout << new_cookware.getCookPrice() << endl;
    cout << new_cookware.getCookBreak() << endl;

    new_cookware.setCookName("spatula");
    new_cookware.setCookPrice(20);
    new_cookware.setCookBreak(15);

    cout << new_cookware.getCookName() << endl;
    cout << new_cookware.getCookPrice() << endl;
    cout << new_cookware.getCookBreak() << endl;

    Cookware cauldron("Cauldron", 40, 5);

    cout << cauldron.getCookName() << endl;
    cout << cauldron.getCookPrice() << endl;
    cout << cauldron.getCookBreak() << endl;

    cauldron.setCookPrice(-20); // negative check works 
    // cookware constructurs, getters, setters, work

    cout << "------" << endl;

    //inventory testing

    Inventory empty_inventory;

    cout << empty_inventory.getNumArmor() << endl;
    cout << empty_inventory.getNumIngredients() << endl;
    cout << empty_inventory.getNumGold() << endl;
    // cout << empty_inventory.getCookwareList() << endl;
    // should match with this
    empty_inventory.printCookwareList(); // print lists working

    // questions I have, can you cout an entire vector
    // can you use a for each loop on user created data types (multiple data members stored in a single object so how would it know which one to print)
    vector<Weapon> weaponList = empty_inventory.getWeaponList();
    empty_inventory.printWeaponList(); 

    // cout << empty_inventory.getTreasureList() << endl;
    empty_inventory.printTreasureList();

    //empty_inventory.setArmor(10);
    empty_inventory.setGold(80);
    empty_inventory.setIngredients(50);

    // would it be worth it to add a function adds a weapon, cookware, treasure?
    // would have to repeat this line, but at same time function would be like one line long
    // deciding to create add function because these lines don't seem to work correctlys
    empty_inventory.addWeapon(Weapon("stick", 5, 5));
    empty_inventory.addCookware(Cookware("pan", 20, 30));
    empty_inventory.addTreasure(Treasure("Ruby", 10)); // add functions working properly

    cout << empty_inventory.getNumArmor() << endl;
    cout << empty_inventory.getNumIngredients() << endl;
    cout << empty_inventory.getNumGold() << endl;

    empty_inventory.printWeaponList();
    empty_inventory.printCookwareList();
    empty_inventory.printTreasureList(); // displays are updating after object has been added to vector

    vector<Weapon> weapons = {Weapon("toy", 10, 11), Weapon("bat", 19, 12), Weapon("remote", 2, 2), Weapon("nunchuk", 8, 16), Weapon("batmobile", 1000, 50)};
    vector<Cookware> cookware = {Cookware("pot", 5, 20), Cookware("fork", 3, 50), Cookware("golden spoon", 30, 20), Cookware("wok", 100, 1), Cookware("cup", 4, 75)};
    vector<Treasure> treasure = {Treasure("Crystal", 40), Treasure("Lapis", 20), Treasure("diamond", 100), Treasure("iron goblet", 35), Treasure("emerald", 15)};

    Inventory full_inventory(treasure, cookware, weapons, 100, 12, 50); // parametrized constructor working

    cout << full_inventory.getNumArmor() << endl;
    cout << full_inventory.getNumIngredients() << endl;
    cout << full_inventory.getNumGold() << endl;

    full_inventory.addCookware(Cookware("should not add", 0, 0)); // cookware check for size works, may implement as a while loop or allow user to remove a cookware to add the one they had
    // might add a setCookwareAt function

    full_inventory.printWeaponList(); // printers working
    full_inventory.printCookwareList();
    full_inventory.printTreasureList();

    full_inventory.setCookwareAt(Cookware("normal spoon", 2, 4), 2);
    full_inventory.setWeaponAt(Weapon("flames", 5, 5), 5); // setters working

    full_inventory.printWeaponList(); // printers working
    full_inventory.printCookwareList();

    full_inventory.inventoryDisplay();

    //testing traveling party

    cout << "------" << endl;

    TravelingParty empty_party; // testing default constructor


    cout << empty_party.getNumRooms() << endl;
    cout << empty_party.getNumKeys() << endl;
    cout << empty_party.getInventory().getNumArmor() << endl; // ensuring that getInventory works correctly, can access member functions from inventory after getting inventory

    empty_party.printPlayerList();
    // expecting a cout saying that there are no players

    // getters are functioning

    // testing setters and other functions

    empty_party.addPlayer(Player("ethan", 20));

    empty_party.printPlayerList();

    empty_party.setNumKeys(2);
    empty_party.setNumRooms(3);

    empty_party.setPlayerAt(Player("theo", 50), 0);

    //empty_party.getInventory().setArmor(20);

    cout << empty_party.getNumRooms() << endl;
    cout << empty_party.getNumKeys() << endl;
    cout << empty_party.getInventory().getNumArmor() << endl; // ensuring that getInventory works correctly, can access member functions from inventory after getting inventory

    empty_party.printPlayerList();

    cout << empty_party.getPlayer(0).getName() << endl;

    vector<Player> get_player_test = empty_party.getPlayerList();

    for(int i = 0; i < get_player_test.size(); i++)
    {
        cout << get_player_test[i].getFullness() << endl;
    }

    cout << "-----" << endl;

    //testing parametrized constructor of the travelingParty class

    vector<Player> party = {Player("tim", 50), Player("jim", 50), Player("bob", 50), Player("smith", 50), Player("john", 50)};

    TravelingParty full_party(party, full_inventory, 0, 0);

    full_party.printPlayerList();

    cout << endl;

    full_party.getInventory().printWeaponList();

    cout << endl;

    cout << full_party.getNumKeys() << endl; // 0
    cout << full_party.getNumRooms() << endl; // 0

    cout << full_party.getInventory().getNumArmor() << endl;


    full_party.getInventory().setArmor(20);

    cout << full_party.getInventory().getNumArmor() << endl; // armor value not updating when I set it previously
    // I know that the setter is being called and executed after putting cout statements in the function
    // however, I don't know why the value is not changing

    cout << "------" << endl;

    cout << full_party.getInventory().getNumGold() << endl;

    full_party.getInventory().setGold(50);

    cout << full_party.getInventory().getNumGold() << endl; // my setters are not working when they are accessed from the getInventory function
    
    cout << "------" << endl;

    full_party.getInventory().setWeaponAt(Weapon("goblin", 10, 100), 4);

    cout << full_party.getInventory().getNumWeapon("goblin") << endl;

    full_party.getInventory().printWeaponList();

    full_party.removePlayer(full_party.getPlayerList().size() -1); // might consider removing the display at the end of remove player

    cout << "------" << endl;

    full_party.printPlayerList();

    full_party.getPlayerList()[0].setFullness(49);

    full_party.printPlayerList();

    cout << "-------" << endl;

    empty_party.setInventory(full_inventory);

    empty_party.getInventory().printWeaponList();

    empty_party.getInventory().setWeaponAt(Weapon("goblin", 10, 100), 4);

    empty_party.getInventory().printWeaponList();

}
The following is a test cpp code show the items from Item.h working.
if you wish for defense you can use the defense class

#include <iostream>
#include "items.h"

int main()
{
    int health = 90;
    int armordefense = 0;
    int shielddefense = 0;
    int attack = 5;

    auto defense = [&]() { return armordefense + shielddefense; };


    std::cout << "Health = " << health;
    std::cout << "\nArmor Defense = " << armordefense;
    std::cout << "\nShield Defense = " << shielddefense;
	std::cout << "\nAttack = " << attack;

    HPotion potion;
    Armor weakarmor;
    Armor strongarmor;
    Armor strongerarmor;
    Shields weaksheild;
	Shields strongsheild;
    Shields strongersheild;
    Swords weaksword;
	Swords strongsword;
	Swords strongersword;

    potion.use(health);
    weaksheild.equipDefense(shielddefense);
    weaksword.equipAttack(attack);
    weakarmor.equipArDefense(armordefense);

    std::cout << "\n\nHeatlh is now " << health << " after using the health potion";
	std::cout << "\n\nArmor Defense is now " << armordefense << " after equipping the armor";
    std::cout << "\n\nshield Defese is now " << shielddefense << " after equipping the shield";
    std::cout << "\n\nTotal Defense would be " << defense() << " after equipping the armor and shield";
	std::cout << "\n\nAttack is now " << attack << " after equipping the sword";

    return 0;
}
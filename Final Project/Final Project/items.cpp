#include <iostream>
#include "Items.h"



Armor::Armor() : Equipment("weakArmor") {
	++ar_count;

	if (ar_count == 1) armorDefend = 4;      // weak
	else if (ar_count == 2) armorDefend = 7; // strong
	else if (ar_count == 3) armorDefend = 10; // stronger
	else armorDefend = 4; // default defense for new armors
}

std::string Armor::getName() const {
	return "Armor";
}

void Armor::equipArDefense(int& armordefense) {
	armordefense = armorDefend;
}







Shields::Shields() : Equipment("weakshield") {
	++sh_count;

	if (sh_count == 1) defend = 4;      // weak
	else if (sh_count == 2) defend = 7; // strong
	else if (sh_count == 3) defend = 10; // stronger
	else defend = 4; // default defense for new armors
}

std::string Shields::getName() const {
	return "Shield";
}

void Shields::equipDefense(int& defense) {
	defense = defend;
}








Swords::Swords() : Equipment("weakshield") {
	++sw_count;

	if (sw_count == 1) attack = 4;      // weak
	else if (sw_count == 2) attack = 7; // strong
	else if (sw_count == 3) attack = 10; // stronger
	else attack = 4; // default defense for new armors
}

std::string Swords::getName() const {
	return "Sword";
}

void Swords::equipAttack(int& attacks) {
	attacks = attack;
}













HPotion::HPotion()
	: consumables("potion"),
healthRegained(7) {}

std::string HPotion::getName() const {
	return "HPotion";
}
void HPotion::use(int& health) {
	if (health + healthRegained > 100) {// If the amount gained from the potion makes the health go past full
		health = 100;                   // just set the health to full instead of going over
	}
	else {
		health += healthRegained;
	}
}
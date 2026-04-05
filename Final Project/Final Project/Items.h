#pragma once
#include <string>
#include <iostream>

/*
This header file is for defining items for the game
If you want to use this file add #include "item.h" to the .cpp file
When you want to import equipment from this file to the main, add (Sword. //name of sword//;)
                                                                  (Sheild. //name of sheild//;)

When you want to equip an item in the main, add (//name of sheild//.equipDefense(////name of defense stat))
                                                (//name of sword//.equipAttack(////name of attack stat))

when you want to import the health potion just add (HPotion potion;)
When you want to use the health potion just add (potion.use(health);)
*/




// top class Items
class Items{
private:
	std::string name;
public:
	Items(std::string n) : name(n) {}
	virtual ~Items() {}

	// equipment and consumables have different behavior. Provide two
	// distinct no-op hooks so subclasses can override only what they need.
	virtual void equipDefense(int& /*defense*/) { }
	virtual void equipAttack(int& /*attack*/) { }
};

//subclass Equipment and consumables
class Equipment : public Items {
private:
	int durability{100};

public:
	Equipment(std::string n) : Items(n) {}
};

class consumables : public Items {
public:
	consumables(std::string n) : Items(n) {}

	// consumables can be used to affect health
	virtual void use(int& health) = 0;
};

//subclass of equipment sheild and sword
class Shields : public Equipment {
private:
	// how much the shield will defend against incoming attack damage
	int defend;

	// simple counter to vary shield strength depending on creation order.
	static inline int sh_count =0;
public:
	// Default constructor: always calls Equipment with a name
	Shields() : Equipment("weakshield") {
		++sh_count;
		if (sh_count == 1) defend = 4;      // weak
		else if (sh_count == 2) defend = 7; // strong
		else if (sh_count == 3) defend = 10; // stronger
		else defend = 4; // default defense for new sheilds
	}

	void equipDefense(int& defense) override {
		defense += defend;
	}
};

// Definition of the static counter. 
//int Shields::sh_count = 0;


class Swords : public Equipment {
private:
	// how much the sword will defend against incoming attack damage
	int attack;

	// simple counter to vary sword strength depending on creation order.
	static inline int sw_count=0;
public:
	// Default constructor: always calls Equipment with a name
	Swords() : Equipment("weaksword") {
		++sw_count;
		if (sw_count == 1) attack = 4;      // weak
		else if (sw_count == 2) attack = 7; // strong
		else if (sw_count == 3) attack = 10; // stronger
		else attack = 4; // default defense for new swords
	}

	void equipAttack(int& attack) override {
		attack += attack;
	}
};

// Definition of the static counter. 
//int Swords::sw_count = 0;

//subclass of consumables Healing Potion(HPotion)
class HPotion : public consumables {
private:
	int healthregained{7};
public:
	HPotion() : consumables("potion") {}
	
	void use(int& health) override {
		health += healthregained;
	}
};

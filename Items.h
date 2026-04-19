#pragma once
#include <string>
#include <iostream>
#include <string>

/*
This header file is for defining items for the game
If you want to use this file add #include "Items.h" to the .h file
When you want to import equipment from this file to the main, add (Armor. //name of armor//;)
																  (Sword. //name of sword//;)
																  (Shield. //name of shield//;)

When you want to equip an item in the main, add (//name of armor//.equipArDefense(////name of armordefense stat))
												(//name of shield//.equipDefense(////name of defense stat))
												(//name of sword//.equipAttack(////name of attack stat))

when you want to import the health potion just add (HPotion potion;)
When you want to use the health potion just add (potion.use(health);)
*/



//============================Items=========================================//

class Items {
public:
	Items(std::string n)
		: name(n)
	{
	}
	virtual ~Items() = default;
	virtual std::string getName() const = 0;
	// equipment and consumables have different behavior. Provide two
	// distinct no-op hooks so subclasses can override only what they need.
	virtual void equipArDefense(int& /*armordefense*/) {}
	virtual void equipDefense(int& /*defense*/) {}
	virtual void equipAttack(int& /*attack*/) {}
private:
	std::string name;
};

//============================Items->Equipment=========================================//

class Equipment : public Items {
public:
	Equipment(std::string n) : Items(n) {}
private:
	int durability{ 100 };
};

//============================Items->Consumables=======================================//

class consumables : public Items {
public:
	consumables(std::string n) : Items(n) {}

	// consumables can be used to affect health
	virtual void use(int& health) = 0;
};

//============================Items->Equipment->Armor======================================//

class Armor : public Equipment {
public:
    Armor();
	// construct armor of a specific tier: 1=weak,2=strong,3=stronger
	explicit Armor(int tier);
	std::string getName() const override;
	void equipArDefense(int& armordefense) override;
private:
	// how much the armor will defend against incoming attack damage
	int armorDefend;

	// simple counter to vary armor strength depending on creation order.
	static inline int ar_count = 0;
};

//============================Items->Equipment->Shields======================================//

class Shields : public Equipment {
public:
	Shields();
	std::string getName() const override;
	void equipDefense(int& defense) override;
private:
	// how much the shield will defend against incoming attack damage
	int defend;

	// simple counter to vary shield strength depending on creation order.
	static inline int sh_count = 0;

};

//============================Items->Equipment->Swords======================================//

class Swords : public Equipment {
public:
	Swords();
	std::string getName() const override;
	void equipAttack(int& attacks) override;
private:
	// how much the sword will defend against incoming attack damage
	int attack;

	// simple counter to vary sword strength depending on creation order.
	static inline int sw_count = 0;
};

//============================Items->Consumables->HPotion======================================//

class HPotion : public consumables {
private:
	int healthRegained;
public:
	HPotion();
	std::string getName() const override;
	void use(int& health) override;
};
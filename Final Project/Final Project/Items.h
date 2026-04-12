#pragma once
#include <string>
#include <iostream>
#include <string>

/*
This header file is for defining items for the game
If you want to use this file add #include "item.h" to the .cpp file
When you want to import equipment from this file to the main, add (Armor. //name of armor//;)
																  (Sword. //name of sword//;)
																  (Shield. //name of shield//;)

When you want to equip an item in the main, add (//name of armor//.equipArDefense(////name of armordefense stat))
												(//name of shield//.equipDefense(////name of defense stat))
												(//name of sword//.equipAttack(////name of attack stat))

when you want to import the health potion just add (HPotion potion;)
When you want to use the health potion just add (potion.use(health);)
*/




// top class Items
class Items {
private:
	std::string name;
public:
	Items(std::string n) : name(n) {}
	virtual ~Items() = default;
	virtual std::string getName() const = 0;
	// equipment and consumables have different behavior. Provide two
	// distinct no-op hooks so subclasses can override only what they need.
	virtual void equipArDefense(int& /*armordefense*/) {}
	virtual void equipDefense(int& /*defense*/) {}
	virtual void equipAttack(int& /*attack*/) {}
};

//subclass Equipment and consumables
class Equipment : public Items {
private:
	int durability{ 100 };

public:
	Equipment(std::string n) : Items(n) {}
};

class consumables : public Items {
public:
	consumables(std::string n) : Items(n) {}

	// consumables can be used to affect health
	virtual void use(int& health) = 0;
};





//subclass of equipment sheild and sword and armor
class Armor : public Equipment {
private:
	// how much the armor will defend against incoming attack damage
	int armordefend;

	// simple counter to vary armor strength depending on creation order.
	static inline int ar_count = 0;
public:
	Armor();
	std::string getName() const override;
	void equipArDefense(int& armordefense) override;
};







class Shields : public Equipment {
private:
	// how much the shield will defend against incoming attack damage
	int defend;

	// simple counter to vary shield strength depending on creation order.
	static inline int sh_count = 0;
public:
	Shields();
	std::string getName() const override;
	void equipDefense(int& defense) override;
	
};








class Swords : public Equipment {
private:
	// how much the sword will defend against incoming attack damage
	int attack;

	// simple counter to vary sword strength depending on creation order.
	static inline int sw_count = 0;
public:
	Swords();
	std::string getName() const override;
	void equipAttack(int& attacks) override;
};







//subclass of consumables Healing Potion(HPotion)
class HPotion : public consumables {
private:
	int healthregained;
public:
	HPotion();
	std::string getName() const override;
	void use(int& health) override;
};
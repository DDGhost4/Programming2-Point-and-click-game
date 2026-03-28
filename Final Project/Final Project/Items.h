
#include <string>
#include <iostream>

//top class Items
class Items{
private:
	std::string name;
public:
	Items(std::string n) : name(n) {}
	virtual ~Items() {}

	virtual void use(int& health) = 0;
};

//subclass Equipment and consumables
class Equipment : public Items {
private:
	int durability;

public:
	

};

class consumables : public Items {
public:
	consumables(std::string n) : Items(n) {}

};

//subclass of equipment sheild and sword
class Sheild : public Equipment {
private: 
	//how much the sheild will defend against incoming attack damage
	int defend{4};
public:

};

class Sword : public Equipment {
private: 
	//how much the sword will increase attack damage
	int attack{5};
public:

};

//subclass of consumables Healing Potion(HPotion)
class HPotion : public consumables {
private:
	int healthregained;
public:
	HPotion() : consumables("potion"), healthregained{7} {}
	
	void use(int& health) override {
		health += healthregained;
	}
};
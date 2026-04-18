#pragma once
#include "Items.h"
#include <memory>
#include <vector>

class Actor
{
public:
    // Constructor
    Actor(int statHealth, int statAttack, int statDefense);
    virtual ~Actor() = default;

    // Actor Actions
    virtual void attack(Actor& target); // return total damage
	bool isAlive() const; // return if the actor is alive 
	virtual void modifyHealth(int value); // change health by a certain value (positive or negative)

	// Getters and setters for stats
    void setHP(int health);
    int getHP() const;

    void setCurrentHP(int currentHealth);
    int getCurrentHP() const;

    void setAtt(int attack);
    int getAtt() const;

    void setDef(int defense);
    int getDef() const;

	void displayStats() const;

private:
    int m_statMaxHP=100;
    int m_statCurrentHP=0;
    int m_statBaseAtt=0;
    int m_statBaseDef=0;
};

class Player : public Actor {
public: 
    using Actor::Actor;
    
    void attack(Actor& target) override;
    
    void modifyHealth(int value) override;

    void equipItem(Items& item);

    void addItem(std::unique_ptr<Items> item);



private: 
    std::vector <std::unique_ptr<Items>> m_inventory;
    int m_bonusAttack{ 0 };
    int m_bonusDefense{ 0 };
    int m_bonusArmor{ 0 };
};

class Enemy : public Actor {
public:
    using Actor::Actor;

    void attack(Actor& target) override;

};


class Skeleton : public Enemy {

public:

    using Enemy::Enemy;
    void attack(Actor& target) override;
};
class Ghost : public Enemy {
public:
    using Enemy::Enemy;
    void attack(Actor& target) override;
};


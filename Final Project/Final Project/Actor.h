#pragma once

#include <vector>

class Actor
{
public:
    // Constructor
    Actor(int statHealth, int statAttack, int statDefense);
    virtual ~Actor() = default;

    // Actor Actions
    int attack() const; // return total damage
	bool isAlive() const; // return if the actor is alive 
	void modifyHealth(int value); // change health by a certain value (positive or negative)

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
    int m_statMaxHP;
    int m_statCurrentHP;
    int m_statBaseAtt;
    int m_statBaseDef;

};




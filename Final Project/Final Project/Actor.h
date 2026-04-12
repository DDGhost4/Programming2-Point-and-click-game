#pragma once

#include <vector>

class Actor
{
public:
    Actor(int statHealth, int statAttack, int statDefense);
    virtual ~Actor() = default;

    int attack() const;

    // Is actor alive (current health > 0)
    bool isAlive() const;

	void modifyHealth(int value);


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




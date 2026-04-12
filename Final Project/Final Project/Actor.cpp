#include "Actor.h"
#include <iostream>

Actor::Actor(int statHealth, int statAttack, int statDefense)
    : m_statMaxHP(statHealth),
      m_statCurrentHP(statHealth),
      m_statBaseAtt(statAttack),
      m_statBaseDef(statDefense)
{ }


int Actor::attack() const
{
    
}

// Actor is alive if current health is greater than 0
bool Actor::isAlive() const
{
    return m_statCurrentHP > 0;
}

// Modify health by a certain value (positive or negative) and ensure it stays within valid bounds
void Actor::modifyHealth(int value)
{
	m_statCurrentHP += value;
    if (m_statCurrentHP > m_statMaxHP) {
        m_statCurrentHP = m_statMaxHP; // Cap at max health
    } else if (m_statCurrentHP < 0) {
        m_statCurrentHP = 0; // Don't go below 0
	}
}


// Getters and setters for stats
void Actor::setHP(int health) { m_statMaxHP = health; }
int Actor::getHP() const { return m_statMaxHP; }

void Actor::setCurrentHP(int currentHealth) { m_statCurrentHP = currentHealth; }
int Actor::getCurrentHP() const { return m_statCurrentHP; }

void Actor::setAtt(int attack) { m_statBaseAtt = attack; }
int Actor::getAtt() const { return m_statBaseAtt; }

void Actor::setDef(int defense) { m_statBaseDef = defense; }
int Actor::getDef() const { return m_statBaseDef; }

void Actor::displayStats() const
{
    std::cout << "Health: " << getCurrentHP() << "/" << getHP()
         << " | Attack: " << getAtt()
		<< " | Defense: " << getDef() << std::endl;
}


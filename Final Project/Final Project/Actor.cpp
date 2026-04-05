#include "Actor.h"
#include <algorithm>
#include <iostream>

Actor::Actor(int statHealth, int statAttack, int statDefense)
    : m_statHealth(std::max(0, statHealth)),
      m_statCurrentHealth(std::max(0, statHealth)),
      m_statAttack(std::max(0, statAttack)),
      m_statDefense(std::max(0, statDefense))
{ }

void Actor::takeDamage(int damage)
{
    if (damage <= 0)
        return;

    // Defense reduces incoming damage; never negative
    int effective = std::max(0, damage - m_statDefense);
    setCurrentHealth(getCurrentHealth() - effective);
}

int Actor::attackDamage(int multiplier) const
{
    if (multiplier <= 0)
        return 0;
    return getAttack() * multiplier;
}

void Actor::heal(int amount)
{
    if (amount <= 0)
        return;
    setCurrentHealth(std::min(getCurrentHealth() + amount, getHealth()));
}

bool Actor::isAlive() const
{
    return getCurrentHealth() > 0;
}

void Actor::setHealth(int health) { m_statHealth = std::max(0, health); 
    // keep current health within new bounds
    m_statCurrentHealth = std::min(m_statCurrentHealth, m_statHealth);
}
int Actor::getHealth() const { return m_statHealth; }

void Actor::setCurrentHealth(int currentHealth)
{
    // clamp between 0 and max health
    m_statCurrentHealth = std::clamp(currentHealth, 0, m_statHealth);
}
int Actor::getCurrentHealth() const { return m_statCurrentHealth; }

void Actor::setAttack(int attack) { m_statAttack = std::max(0, attack); }
int Actor::getAttack() const { return m_statAttack; }

void Actor::setDefense(int defense) { m_statDefense = std::max(0, defense); }
int Actor::getDefense() const { return m_statDefense; }

void Actor::displayStats() const
{
    std::cout << "Health: " << getCurrentHealth() << "/" << getHealth()
         << " | Attack: " << getAttack()
		<< " | Defense: " << getDefense() << std::endl;
}


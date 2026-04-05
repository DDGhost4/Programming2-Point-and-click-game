#include "Actor.h"
#include <iostream>

Actor::Actor(int statHealth, int statAttack, int statDefense)
	: m_statHealth(statHealth),
	m_statCurrentHealth(statHealth),
	m_statAttack(statAttack),
	m_statDefense(statDefense)
{};

void Actor::setHealth(int health) { m_statHealth = health; }
int Actor::getHealth() const { return m_statHealth; }

void Actor::setCurrentHealth(int currentHealth) { m_statCurrentHealth = currentHealth; }
int Actor::getCurrentHealth() const { return m_statCurrentHealth; }

void Actor::setAttack(int attack) { m_statAttack = attack; }
int Actor::getAttack() const { return m_statAttack; }

void Actor::setDefense(int defense) { m_statDefense = defense; }
int Actor::getDefense() const { return m_statDefense; }


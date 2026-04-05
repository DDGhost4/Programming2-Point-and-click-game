#include "Player.h"

Player::Player(int statHealth, int statAttack, int statDefense)
	: Actor(statHealth, statAttack, statDefense)
{};

int Player::attack(int m_statAttack, int damageMultiplier)
{
	return m_statAttack * damageMultiplier;
}

void Player::takeDamage(int damage) {
	int m_statCurrentHealth = getCurrentHealth() - damage;
}


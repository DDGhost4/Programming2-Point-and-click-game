#include "Actor.h"
#include <iostream>
#include <format>
//ACTOR SECTION
Actor::Actor(int statHealth, int statAttack, int statDefense)
    : m_statMaxHP(statHealth),
      m_statCurrentHP(statHealth),
      m_statBaseAtt(statAttack),
      m_statBaseDef(statDefense)
{ }


void Actor::attack(Actor&target)
{
    int damage = m_statBaseAtt;
    target.modifyHealth(-damage);
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



// PLAYER SECTION
void Player::attack(Actor& target)
{
    int totalAttack = getAtt() + m_bonusAttack;
    int damage = totalAttack;

    target.modifyHealth(-damage);
}

void Player::equipItem(Items& item) {
    item.equipAttack(m_bonusAttack);
    item.equipDefense(m_bonusDefense);
    item.equipArDefense(m_bonusArmor);
}


void Player::modifyHealth(int value) {

    if (value < 0) {
        int totalDefense = getDef() + m_bonusDefense + m_bonusArmor;
        int reduced = value + totalDefense; //reduced damaged due to defense modifiers
            if (reduced >= 0) {
                reduced = 0;
        }
            Actor::modifyHealth(reduced);
    }
    
    else {
        Actor::modifyHealth(value);
    }

}

void Player::addItem(std::unique_ptr<Items> item) {
    m_inventory.push_back(std::move(item));
}
// ENEMIES/ENEMY SECTION

void Enemy::attack(Actor& target) {
    int damage = getAtt();
    target.modifyHealth(-damage);
}

void Skeleton::attack(Actor& target) {
        int damage = getAtt()+;
        target.modifyHealth(-damage);
        std::cout << "Skeleton attacks!";
}
void Ghost::attack(Actor& target) {
    int damage = getAtt();
    target.Actor::modifyHealth(-damage);
    std::cout << "Ghost passes through your defenses and attacks!";
}


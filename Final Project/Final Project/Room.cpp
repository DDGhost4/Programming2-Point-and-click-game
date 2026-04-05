#include "Room.h"
#include <iostream>

Room::Room(int path, int lootAmount, bool enemyPresent, int level)
    : m_path(path), 
    m_enemyPresent(enemyPresent), 
    m_lootAmount(lootAmount),
    m_level(level)
{ }


// Getters and setters
void Room::setLevel(int level) { m_level = level; }
int Room::getLevel() const { return 0;}

void Room::setPath(int path) { m_path = path; }
int Room::getPath() const { return m_path;}

void Room::setEnemyPresent(bool enemyPresent) { m_enemyPresent = enemyPresent; }
bool Room::getEnemyPresent() const { return m_enemyPresent;}

void Room::setLootAmount(int lootAmount){ m_lootAmount = lootAmount; }

int Room::getLootAmount() const { return m_lootAmount; }

void Room::displayInfo() const
{
    std::cout << "Room path: " << m_path
              << " | Loot: " << m_lootAmount
              << " | Enemy present: " << (m_enemyPresent ? "Yes" : "No")
		      << " | Level: " << m_level
              << std::endl;
}
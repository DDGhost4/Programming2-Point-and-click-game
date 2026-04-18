#pragma once

class Room
{
public:
	Room(int path, int lootAmount, bool enemyPresent, int level);

	// Getters and setters
	void setLevel(int level);
	int getLevel() const;

	void setPath(int path);
	int getPath() const;

	void setEnemyPresent(bool enemyPresent);
	bool getEnemyPresent() const;

	void setLootAmount(int lootAmount);
	int getLootAmount() const;

	void displayInfo() const;

private:

	int m_path; // Number of paths leading out of the room (1 to 3)
	bool m_enemyPresent; // Whether an enemy is present in the room
	int m_lootAmount; // Amount of loot in the room (0 or more)
	int m_level; // Progress level of the room (1 to 9)
};

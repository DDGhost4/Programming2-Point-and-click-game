#pragma once
class Room
{
public:
	Room(int path, int lootAmount, bool enemyPresent);

	void setPath(int path);
	int getPath() const;

	void setEnemyPresent(bool enemyPresent);
	bool getEnemyPresent() const;

	void setLootAmount(int lootAmount);
	int getLootAmount() const;

	void displayInfo() const;

private:
	int m_paths;
	bool m_enemyPresent;
	int m_lootAmount;
};


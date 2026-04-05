#pragma once

class Room
{
public:
	Room(int path, int item, bool enemyPresent);
private:
	int m_path;
	int m_item;
	bool m_enemyPresent;
};
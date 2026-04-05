#pragma once
class Actor
{
public:
	Actor(int statHealth, int statAttack, int statDefense)
		: m_health(statHealth), m_attack(statAttack), m_defense(statDefense) {};
	virtual ~Actor() = default;
private:
	int m_health;
	int m_attack;
	int m_defense;
};


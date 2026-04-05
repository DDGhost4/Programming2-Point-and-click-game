#pragma once
class Actor
{
public:
	Actor(int statHealth, int statAttack, int statDefense);
	virtual ~Actor() = default;

	void setHealth(int health);
	int getHealth() const;
	
	void setCurrentHealth(int currentHealth);
	int getCurrentHealth() const;
	
	void setAttack(int attack);
	int getAttack() const;
	
	void setDefense(int defense);
	int getDefense() const;

private:
	int m_statHealth;
	int m_statCurrentHealth;
	int m_statAttack;
	int m_statDefense;
	
};


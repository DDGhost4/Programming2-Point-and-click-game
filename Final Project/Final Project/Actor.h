#pragma once
class Actor
{
public:
    Actor(int statHealth, int statAttack, int statDefense);
    virtual ~Actor() = default;

    // Apply damage to this actor. Damage is reduced by this actor's defense.
    void takeDamage(int damage);

    // Compute outgoing attack damage given a multiplier.
    int attackDamage(int multiplier) const;

    // Restore health (clamped to max).
    void heal(int amount);

    // Is actor alive (current health > 0)
    bool isAlive() const;


	// Getters and setters for stats
    void setHealth(int health);
    int getHealth() const;

    void setCurrentHealth(int currentHealth);
    int getCurrentHealth() const;

    void setAttack(int attack);
    int getAttack() const;

    void setDefense(int defense);
    int getDefense() const;

	void displayStats() const;

private:
    int m_statHealth;
    int m_statCurrentHealth;
    int m_statAttack;
    int m_statDefense;
};



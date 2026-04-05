#pragma once
#include "Actor.h"
class Player :
    public Actor
{
public:
    Player(int statHealth, int statAttack, int statDefense);

    int attack(int m_statAttack, int damageMultiplier);

    void takeDamage(int damage);
    
};


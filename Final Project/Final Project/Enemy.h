#pragma once
#include "Actor.h"

class Enemy :
    public Actor
{
public:
    Enemy(int statHealth, int statAttack, int statDefense);
};


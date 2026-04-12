#pragma once
#include "Actor.h"


class Combat
{
public:
	Combat(Actor player, Actor Enemy);

	void startCombat();

private:
	Actor m_player;
	Actor m_enemy;
};


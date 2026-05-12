#pragma once
#include "StateBase.h"

class Enemy;
class EnemyStateBase : public StateBase
{
protected:
	Enemy* GetEnemy(Enemy* a_pEnemy)
	{
		return static_cast<Enemy*>(Owner);
	}
};
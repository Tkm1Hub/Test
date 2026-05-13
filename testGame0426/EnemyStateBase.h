#pragma once
#include "StateBase.h"

class Enemy;
class EnemyStateBase : public StateBase
{
protected:
	Enemy* GetEnemy();
};
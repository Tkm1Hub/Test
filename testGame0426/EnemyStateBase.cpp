#include "stdafx.h"
#include "EnemyStateBase.h"
#include "Enemy.h"

Enemy* EnemyStateBase::GetEnemy()
{
	return static_cast<Enemy*>(Owner);
}
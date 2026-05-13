#include "stdafx.h"
#include "EnemyAttackState.h"
#include "Enemy.h"

void EnemyAttackState::OnStart()
{

}

void EnemyAttackState::OnUpdate()
{
	GetEnemy()->Attack();
}

void EnemyAttackState::OnExit()
{

}

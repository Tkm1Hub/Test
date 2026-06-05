#include "stdafx.h"
#include "EnemyChaseState.h"
#include "EnemyAttackState.h"
#include "Enemy.h"

void EnemyChaseState::OnStart()
{
	GetEnemy()->PlayAnimation((int)(EnemyAnimState::Chase), true);
}

void EnemyChaseState::OnUpdate()
{
	auto enemy = GetEnemy();
	if (!enemy) return;

	// ’ÇÕ
	enemy->Chase();

}

void EnemyChaseState::OnExit()
{

}

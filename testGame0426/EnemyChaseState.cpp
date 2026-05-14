#include "stdafx.h"
#include "EnemyChaseState.h"
#include "EnemyAttackState.h"
#include "Enemy.h"

void EnemyChaseState::OnStart()
{

}

void EnemyChaseState::OnUpdate()
{
	auto enemy = GetEnemy();
	if (!enemy) return;

	// ’ÇÕ
	enemy->Chase();

	// Player‚ªUŒ‚”ÍˆÍ“à‚É“ü‚é‚ÆAttackState
	if (enemy->GetDistanceToPlayer() <= enemy->GetAttackRange())
	{
		auto state = std::make_shared<EnemyAttackState>();
		enemy->ChangeState(state);
	}
}

void EnemyChaseState::OnExit()
{

}

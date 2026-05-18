#include "stdafx.h"
#include "EnemyCombatIdleState.h"
#include "EnemyChaseState.h"
#include "EnemyAttackState.h"
#include "Enemy.h"
#include "AttackToken.h"

void EnemyCombatIdleState::OnStart()
{

}

void EnemyCombatIdleState::OnUpdate()
{
	// enemy取得
	auto enemy = GetEnemy();
	if (!enemy) return;

	//プレイヤー方向を向く
	enemy->SetLookDir(enemy->GetDirectionToPlayer());

	// 攻撃クールダウン中は早期リターン
	if (enemy->GetAttackCoolDown() > 0.0f) return;

	// 攻撃権要求
	if (AttackToken::GetInstance().RequestToken(enemy))
	{
		// 攻撃権取得成功
		auto state = std::make_shared<EnemyChaseState>();
		enemy->ChangeState(state);
		return;
	}
	else
	{
		// 攻撃権未所持
		auto state = std::make_shared<EnemyCombatIdleState>();
		enemy->ChangeState(state);
		return;
	}
}

void EnemyCombatIdleState::OnExit()
{

}

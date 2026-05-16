#include "stdafx.h"
#include "EnemyDeadState.h"
#include "Enemy.h"
#include "Time.h"

void EnemyDeadState::OnStart()
{
	auto enemy = GetEnemy();
	if (!enemy) return;

	// 当たり判定OFF
	enemy->SetIsCollisionEnabled(false);

	// 死亡アニメーション再生など
}

void EnemyDeadState::OnUpdate()
{
	auto enemy = GetEnemy();
	if (!enemy) return;

	timer += Time::GetInstance().GetDeltaTime();

	// 徐々に停止させる
	//VECTOR velocity = enemy->GetExternalVelocity();

	//velocity.x *= 0.9f;
	//velocity.z *= 0.9f;

	//enemy->SetExternalVelocity(velocity);

	// 一定時間後削除
	if (timer >= destroyTime)
	{
		enemy->Destroy();
	}
}

void EnemyDeadState::OnExit()
{
}
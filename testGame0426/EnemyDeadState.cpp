#include "stdafx.h"
#include "EnemyDeadState.h"
#include "Enemy.h"
#include "Time.h"

void EnemyDeadState::OnStart()
{
	auto enemy = GetEnemy();
	if (!enemy) return;

	// ˆÚ“®’âŽ~
	enemy->SetMoveVelocity(VGet(0.0f, 0.0f, 0.0f));
	enemy->SetExternalVelocity(VGet(0.0f, 0.0f, 0.0f));

	// “–‚½‚è”»’èOFF
	enemy->SetIsCollisionEnabled(false);

	// Ž€–SƒAƒjƒ[ƒVƒ‡ƒ“Ä¶‚È‚Ç
}

void EnemyDeadState::OnUpdate()
{
	auto enemy = GetEnemy();
	if (!enemy) return;

	timer += Time::GetInstance().GetDeltaTime();

	// ™X‚É’âŽ~‚³‚¹‚é
	VECTOR velocity = enemy->GetExternalVelocity();

	velocity.x *= 0.9f;
	velocity.z *= 0.9f;

	enemy->SetExternalVelocity(velocity);

	// ˆê’èŽžŠÔŒãíœ
	if (timer >= destroyTime)
	{
		enemy->Destroy();
	}
}

void EnemyDeadState::OnExit()
{
}
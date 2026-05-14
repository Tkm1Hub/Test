#include "stdafx.h"
#include "EnemyAttackState.h"
#include "EnemyChaseState.h"
#include "Enemy.h"
#include "Time.h"

void EnemyAttackState::OnStart()
{

}

void EnemyAttackState::OnUpdate()
{
	// enemy取得
	auto enemy = GetEnemy();
	if (!enemy) return;

	// タイマー
	float dt = Time::GetInstance().GetScaledDeltaTime() * 60.0f;
	timer += dt;

	// 攻撃データ取得
	const AttackData& attackData = enemy->GetAttackData();

	// 現在段
	const AttackStep& step = attackData.combo[currentStep];

	switch (phase)
	{
		// ===== 予備動作 =====
	case AttackPhase::Windup:
		//プレイヤー方向を向く
		enemy->SetLookDir(enemy->GetDirectionToPlayer());

		if (timer >= step.windupTime)
		{
			timer = 0.0f;
			phase = AttackPhase::Active;
			hasHit = false;
		}
		break;

		// ===== 攻撃 =====
	case AttackPhase::Active:
		if (!hasHit)
		{
			enemy->Attack(step);
			hasHit = true;
		}

		if (timer >= step.activeTime)
		{
			timer = 0.0f;
			phase = AttackPhase::Recovery;
		}
		break;

		// ===== 後隙 =====
	case AttackPhase::Recovery:
		//プレイヤー方向を向く
		enemy->SetLookDir(enemy->GetDirectionToPlayer());

		if (timer >= step.recoveryTime)
		{
			timer = 0.0f;
			currentStep++;

			// コンボ終了
			if (currentStep >= attackData.combo.size())
			{
				// 追跡に戻る
				auto state = std::make_shared<EnemyChaseState>();
				enemy->ChangeState(state);
			}
			else
			{
				// 次段へ
				phase = AttackPhase::Windup;
			}
		}
		break;
	}

}

void EnemyAttackState::OnExit()
{

}

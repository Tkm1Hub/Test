#include "stdafx.h"
#include "EnemyAttackState.h"
#include "EnemyCombatIdleState.h"
#include "Enemy.h"
#include "Time.h"
#include "AttackToken.h"
#include "EffectContainer.h"

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
				// CombatIdleに戻る
				auto state = std::make_shared<EnemyCombatIdleState>();
				enemy->ChangeState(state);
				return;
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
	// enemy取得
	auto enemy = GetEnemy();
	if (!enemy) return;

	// 攻撃権を棄権
	AttackToken::GetInstance().ReleaseToken(enemy);

	// クールダウン設定
	enemy->SetAttackCooldown(enemy->GetParam().attackCooldown);
}

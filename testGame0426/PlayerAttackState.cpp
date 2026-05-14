#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerAttackState.h"
#include "Time.h"

void PlayerAttackState::OnStart()
{

}

void PlayerAttackState::OnUpdate()
{
	// player取得
	auto player = GetPlayer();
	if (!player) return;

	// タイマー
	timer += Time::GetInstance().GetDeltaTime() * 60;

	// 攻撃データ取得
	const AttackData& attackData = player->GetAttackData();

	// 現在段
	const AttackStep& step = attackData.combo[currentStep];

	switch (phase)
	{
		// ===== 攻撃 =====
	case AttackPhase::Active:
		if (!hasHit)
		{
			player->Attack(step);
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
		if (timer >= step.recoveryTime)
		{
			timer = 0.0f;
			currentStep++;

			// コンボ終了
			if (currentStep >= attackData.combo.size())
			{
				// スティック操作の有無で Walk or Idle
				if (Input::GetInput().GetIsMoveLStick())
				{
					// Walk
					auto state = std::make_shared<PlayerWalkState>();
					GetPlayer()->ChangeState(state);
					return;
				}
				else
				{
					// Idle
					auto state = std::make_shared<PlayerIdleState>();
					GetPlayer()->ChangeState(state);
					return;
				}
			}
			else
			{
				// 次段へ
				phase = AttackPhase::Active;
			}
		}
		break;
	}
}

void PlayerAttackState::OnExit()
{

}
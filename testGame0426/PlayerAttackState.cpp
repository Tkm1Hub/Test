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

	//--------------------------------
	// 次コンボ入力受付
	//--------------------------------

	if (phase == AttackPhase::Active ||
		phase == AttackPhase::Recovery)
	{
		if (Input::GetInput().IsTrigger(XINPUT_BUTTON_X))
		{
			nextComboRequested = true;
		}
	}

	switch (phase)
	{
		// ===== 準備 =====
	case AttackPhase::Windup:

		if (timer >= step.windupTime)
		{
			timer = 0.0f;

			phase = AttackPhase::Active;
		}

		break;

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

			//--------------------------------
			// 次コンボへ
			//--------------------------------

			if (nextComboRequested &&
				currentStep + 1 < attackData.combo.size())
			{
				currentStep++;

				phase = AttackPhase::Windup;

				hasHit = false;

				nextComboRequested = false;

				return;
			}

			//--------------------------------
			// コンボ終了
			//--------------------------------

			if (Input::GetInput().GetIsMoveLStick())
			{
				auto state =
					std::make_shared<PlayerWalkState>();

				player->ChangeState(state);
			}
			else
			{
				auto state =
					std::make_shared<PlayerIdleState>();

				player->ChangeState(state);
			}

			return;
		}
		break;
	}
}

void PlayerAttackState::OnExit()
{

}
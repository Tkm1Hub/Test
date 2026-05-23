#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerFireState.h"
#include "PlayerAimState.h"
#include "Time.h"

void PlayerFireState::OnStart()
{
}

void PlayerFireState::OnUpdate()
{
	// Player取得
	auto player = GetPlayer();
	if (!player) return;

	// タイマー
	float dt = Time::GetInstance().GetScaledDeltaTime() * 60.0f;
	fireTimer += dt;

	// 攻撃データ取得
	const AttackStep& fireData = player->GetFireData();

	switch (phase)
	{
		// ===== 予備動作 =====
	case AttackPhase::Windup:
		if (fireTimer >= fireData.windupTime)
		{
			fireTimer = 0.0f;
			phase = AttackPhase::Active;
			hasHit = false;
		}
		break;

		// ===== 射撃 =====
	case AttackPhase::Active:
		if (!hasHit)
		{
			player->Fire(fireData);
			hasHit = true;
		}

		if (fireTimer >= fireData.activeTime)
		{
			fireTimer = 0.0f;
			phase = AttackPhase::Recovery;
		}
		break;

		// ===== 後隙 =====
	case AttackPhase::Recovery:

		// 時間が経過したらステート変更
		if (fireTimer >=
			fireData.recoveryTime)
		{
			// 左トリガーが離されたらステート変更
			if (Input::GetInput().GetLeftTrigger() < GetPlayer()->GetParam().aimTriggerDeadZone)
			{
				GetPlayer()->SetIsAim(false);

				// Walk
				if (Input::GetInput().GetIsMoveLStick())
				{
					auto state = std::make_shared<PlayerWalkState>();
					GetPlayer()->ChangeState(state);
					return;
				}
				// Idle
				else
				{
					auto state = std::make_shared<PlayerIdleState>();
					GetPlayer()->ChangeState(state);
					return;
				}
			}
			else
			{
				// 左トリガーが離れていなかったらAim
				auto state = std::make_shared<PlayerAimState>();
				GetPlayer()->ChangeState(state);
				return;
			}
		}
		break;
	}
}

void PlayerFireState::OnExit()
{
}
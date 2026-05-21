#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerJustDodgeState.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"
#include "PlayerWalkState.h"
#include "Time.h"

void PlayerJustDodgeState::OnStart()
{
	Time::GetInstance().SetTimeScale(0.2f);
}

void PlayerJustDodgeState::OnUpdate()
{
	justDodgeTimer += Time::GetInstance().GetDeltaTime();

	// 回避時間が経過したらステート変更
	if (justDodgeTimer >=
		justDodgeTime)
	{
		// Xボタンで攻撃
		if (Input::GetInput().IsTrigger(XINPUT_BUTTON_X))
		{
			auto state = std::make_shared<PlayerAttackState>();
			GetPlayer()->ChangeState(state);
			return;
		}
		// スティック操作の有無で Walk or Idle
		else if (Input::GetInput().GetIsMoveLStick())
		{
			// Walk
			auto state =
				std::make_shared<PlayerWalkState>();

			GetPlayer()->ChangeState(state);
		}
		else
		{
			// Idle
			auto state =
				std::make_shared<PlayerIdleState>();

			GetPlayer()->ChangeState(state);
		}
	}
}

void PlayerJustDodgeState::OnExit()
{
	Time::GetInstance().SetTimeScale(1.0f);
}
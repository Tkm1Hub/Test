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
	Time::GetInstance().SetWorldTimeScale(0.2f);
	GetPlayer()->AddBullet();
}

void PlayerJustDodgeState::OnUpdate()
{
	justDodgeTimer += Time::GetInstance().GetDeltaTime();

	float t =
		justDodgeTimer / justDodgeTime;

	t = std::clamp(
		t,
		0.0f,
		1.0f
	);

	//---------------------------------
	// EaseInQuad
	//---------------------------------

	float ease = t * t * t;

	float timeScale =
		0.2f +
		(1.0f - 0.2f) * ease;

	Time::GetInstance().SetWorldTimeScale(timeScale);

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
	Time::GetInstance().SetWorldTimeScale(1.0f);
}
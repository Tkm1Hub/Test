#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerAimState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerFireState.h"
#include "Enemy.h"
#include "Time.h"

void PlayerAimState::OnStart()
{
	GetPlayer()->SetIsAim(true);
}

void PlayerAimState::OnUpdate()
{
	GetPlayer()->MoveInput();

	auto target = GetPlayer()->GetTarget().lock();

	if (!target ||
		target->IsDead())
	{
		GetPlayer()->SetIsAim(false);

		auto state =
			std::make_shared<PlayerIdleState>();

		GetPlayer()->ChangeState(state);

		return;
	}
	
	// 左トリガーが離されたらステート変更
	if ( 
		Input::GetInput().GetLeftTrigger()
		< GetPlayer()->GetParam().aimTriggerDeadZone)
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

	// 右トリガーが押されたら射撃
	if (Input::GetInput().GetRightTrigger() > GetPlayer()->GetParam().fireTriggerDeadZone)
	{
		auto state = std::make_shared<PlayerFireState>();
		GetPlayer()->ChangeState(state);
		return;
	}
}

void PlayerAimState::OnExit()
{
}
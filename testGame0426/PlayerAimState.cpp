#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerAimState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "Time.h"

void PlayerAimState::OnStart()
{
}

void PlayerAimState::OnUpdate()
{
	GetPlayer()->MoveInput();

	// 左トリガーが離されたらステート変更
	if (Input::GetInput().GetLeftTrigger() < GetPlayer()->GetParam().aimTriggerDeadZone)
	{
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
}

void PlayerAimState::OnExit()
{
}
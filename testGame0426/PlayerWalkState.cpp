#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerDodgeState.h"

void PlayerWalkState::OnStart()
{

}

void PlayerWalkState::OnUpdate()
{
	GetPlayer()->MoveInput();

	// 左スティックが入力なしならIdle
	if (!Input::GetInput().GetIsMoveLStick())
	{
		auto state = std::make_shared<PlayerIdleState>();
		GetPlayer()->ChangeState(state);
		return;
	}

	// Aボタンでジャンプ
	if (Input::GetInput().GetNowFrameNewInput() & 16)
	{
		auto state = std::make_shared<PlayerJumpState>();
		GetPlayer()->ChangeState(state);
		return;
	}

	// Rボタンで回避
	if (Input::GetInput().GetNowFrameNewInput() & 516)
	{
		auto state = std::make_shared<PlayerDodgeState>();
		GetPlayer()->ChangeState(state);
		return;
	}

}

void PlayerWalkState::OnExit()
{

}
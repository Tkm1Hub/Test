#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"

void PlayerWalkState::OnStart()
{

}

void PlayerWalkState::OnUpdate()
{
	player->MoveInput();

	// 左スティックが入力なしならIdle
	if (!Input::GetInput().GetIsMoveLStick())
	{
		auto spIdleState = std::make_shared<PlayerIdleState>();
		player->ChangeState(spIdleState);
		return;
	}

	// Aボタンでジャンプ
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<PlayerJumpState>();
		player->ChangeState(spJumpState);
		return;
	}
}

void PlayerWalkState::OnExit()
{

}
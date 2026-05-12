#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"

void PlayerIdleState::OnStart()
{

}

void PlayerIdleState::OnUpdate()
{
	// 左スティックが入力中なら移動
	if (Input::GetInput().GetIsMoveLStick())
	{
		auto spWalkState = std::make_shared<PlayerWalkState>();
		GetPlayer()->ChangeState(spWalkState);
		return;
	}

	// Aボタンでジャンプ
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<PlayerJumpState>();
		GetPlayer()->ChangeState(spJumpState);
		return;
	}
}

void PlayerIdleState::OnExit()
{

}
#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerFallState.h"
#include "PlayerDodgeState.h"
#include "PlayerAttackState.h"

void PlayerIdleState::OnStart()
{

}

void PlayerIdleState::OnUpdate()
{
	// 左スティックが入力中なら移動
	if (Input::GetInput().GetIsMoveLStick())
	{
		auto state = std::make_shared<PlayerWalkState>();
		GetPlayer()->ChangeState(state);
		return;
	}

	// Aボタンでジャンプ
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_A))
	{
		auto state = std::make_shared<PlayerJumpState>();
		GetPlayer()->ChangeState(state);
		return;
	}

	// Rボタンで回避
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		auto state = std::make_shared<PlayerDodgeState>();
		GetPlayer()->ChangeState(state);
		return;
	}

	// Xボタンで攻撃
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_X))
	{
		auto state = std::make_shared<PlayerAttackState>();
		GetPlayer()->ChangeState(state);
		return;
	}

	// verticalVelocityが０以下ならFall
	if (GetPlayer()->GetVerticalVelocity() < 0.0f)
	{
		auto state = std::make_shared<PlayerFallState>();
		GetPlayer()->ChangeState(state);
		return;
	}
}

void PlayerIdleState::OnExit()
{

}
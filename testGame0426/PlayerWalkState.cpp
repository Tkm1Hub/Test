#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerDodgeState.h"
#include "PlayerAttackState.h"
#include "PlayerFallState.h"
#include "PlayerAimState.h"
#include "PlayerBlockState.h"

void PlayerWalkState::OnStart()
{
	GetPlayer()->PlayAnimation((int)(PlayerAnimState::Walk), true);
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

	// Lボタンでガード
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		auto state = std::make_shared<PlayerBlockState>();
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

	// Lトリガーでエイム
	auto target = GetPlayer()->GetTarget().lock();
	if (target)
	{
		if (Input::GetInput().GetLeftTrigger() >= GetPlayer()->GetParam().aimTriggerDeadZone)
		{
			auto state = std::make_shared<PlayerAimState>();
			GetPlayer()->ChangeState(state);
			return;
		}
	}

	// verticalVelocityが０以下ならFall
	if (GetPlayer()->GetVerticalVelocity() < 0.0f)
	{
		auto state = std::make_shared<PlayerFallState>();
		GetPlayer()->ChangeState(state);
		return;
	}
}

void PlayerWalkState::OnExit()
{

}
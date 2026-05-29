#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerJumpState.h"
#include "PlayerFallState.h"

void PlayerJumpState::OnStart()
{
	// ジャンプ力を加算
	GetPlayer()->AddVerticalVelocity(
		GetPlayer()->GetParam().jumpPower
	);

	// 着地フラグをFalseに
	GetPlayer()->SetIsGraund(false);

	// アニメ再生
	GetPlayer()->PlayAnimation((int)(PlayerAnimState::JumpUp), false);
}

void PlayerJumpState::OnUpdate()
{
	GetPlayer()->MoveInput();

	// verticalVelocityが０以下ならFall
	if (GetPlayer()->GetVerticalVelocity() < 0.0f)
	{
		auto state = std::make_shared<PlayerFallState>();
		GetPlayer()->ChangeState(state);
		return;
	}
}

void PlayerJumpState::OnExit()
{

}
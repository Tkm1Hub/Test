#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerJumpState.h"
#include "PlayerFallState.h"

void PlayerJumpState::OnStart()
{
	// ジャンプ力を加算
	GetPlayer()->SetVerticalVelocity(
		GetPlayer()->GetJumpPower()
	);

	// 着地フラグをFalseに
	GetPlayer()->SetIsGraund(false);
}

void PlayerJumpState::OnUpdate()
{
	GetPlayer()->MoveInput();

	// verticalVelocityが０以下ならFall
	if (GetPlayer()->GetVerticalVelocity() < 0.0f)
	{
		auto spFallState = std::make_shared<PlayerFallState>();
		GetPlayer()->ChangeState(spFallState);
		return;
	}
}

void PlayerJumpState::OnExit()
{

}
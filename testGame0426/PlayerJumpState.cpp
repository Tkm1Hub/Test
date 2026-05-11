#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerJumpState.h"
#include "PlayerFallState.h"

void PlayerJumpState::OnStart()
{
	// ジャンプ力を加算
	player->SetVerticalVelocity(
		player->GetJumpPower()
	);

	// 着地フラグをFalseに
	player->SetIsGraund(false);
}

void PlayerJumpState::OnUpdate()
{
	player->MoveInput();

	// verticalVelocityが０以下ならFall
	if (player->GetVerticalVelocity() < 0.0f)
	{
		auto spFallState = std::make_shared<PlayerFallState>();
		player->ChangeState(spFallState);
		return;
	}
}

void PlayerJumpState::OnExit()
{

}
#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerFallState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"

void PlayerFallState::OnStart()
{

}

void PlayerFallState::OnUpdate()
{
	player->MoveInput();

	// pos.yが０以下ならIdle or Walk
	if (player->GetPosition().y > 0.0f) return;

	// 左スティックの操作中かどうかで分岐
	if (!Input::GetInput().GetIsMoveLStick())
	{
		// Idle
		auto spIdleState = std::make_shared<PlayerIdleState>();
		player->ChangeState(spIdleState);
		return;
	}
	else
	{
		// Walk
		auto spWalkState = std::make_shared<PlayerWalkState>();
		player->ChangeState(spWalkState);
		return;
	}
}

void PlayerFallState::OnExit()
{
	player->SetIsGraund(true);
}
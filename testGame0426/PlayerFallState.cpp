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
	GetPlayer()->MoveInput();

	// pos.yが０以下ならIdle or Walk
	if (GetPlayer()->GetPosition().y > 0.0f) return;

	// 左スティックの操作中かどうかで分岐
	if (!Input::GetInput().GetIsMoveLStick())
	{
		// Idle
		auto spIdleState = std::make_shared<PlayerIdleState>();
		GetPlayer()->ChangeState(spIdleState);
		return;
	}
	else
	{
		// Walk
		auto spWalkState = std::make_shared<PlayerWalkState>();
		GetPlayer()->ChangeState(spWalkState);
		return;
	}
}

void PlayerFallState::OnExit()
{
	GetPlayer()->SetIsGraund(true);
}
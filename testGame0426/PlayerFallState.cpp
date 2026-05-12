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
		auto state = std::make_shared<PlayerIdleState>();
		GetPlayer()->ChangeState(state);
		return;
	}
	else
	{
		// Walk
		auto state = std::make_shared<PlayerWalkState>();
		GetPlayer()->ChangeState(state);
		return;
	}
}

void PlayerFallState::OnExit()
{
	GetPlayer()->SetIsGraund(true);
}
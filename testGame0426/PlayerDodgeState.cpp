#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerDodgeState.h"
#include "Enemy.h"
#include "Time.h"

void PlayerDodgeState::OnStart()
{
	VECTOR dodgeDir = GetPlayer()->GetInputDir();

	auto player = GetPlayer();

	auto target = player->GetTarget().lock();

	// 入力が無ければ前方向を使用
	if (VSize(dodgeDir) <= 0.1f)
	{
		dodgeDir = player->GetForward();

		if (target)
		{
			VECTOR targetDir =
				VSub(
					target->GetPosition(),
					player->GetPosition()
				);
			targetDir = VNorm(targetDir);
			dodgeDir = VScale(targetDir, -1);
		}
	}

	player->SetExternalVelocity(
		VScale(dodgeDir, player->GetParam().dodgeSpeed)
	);

	player->SetExtraHitRadius(player->GetParam().extraHitRadius);
}

void PlayerDodgeState::OnUpdate()
{

	dodgeTimer += Time::GetInstance().GetDeltaTime();

	// 回避時間が経過したらステート変更
	if (dodgeTimer >=
		GetPlayer()->GetParam().dodgeTime)
	{
		// スティック操作の有無で Walk or Idle
		if (Input::GetInput().GetIsMoveLStick())
		{
			// Walk
			auto state =
				std::make_shared<PlayerWalkState>();

			GetPlayer()->ChangeState(state);
		}
		else
		{
			// Idle
			auto state =
				std::make_shared<PlayerIdleState>();

			GetPlayer()->ChangeState(state);
		}
	}
}

void PlayerDodgeState::OnExit()
{
	GetPlayer()->SetExtraHitRadius(0.0f);
}
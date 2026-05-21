#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerDodgeState.h"
#include "Time.h"

void PlayerDodgeState::OnStart()
{
	VECTOR dodgeDir = GetPlayer()->GetMoveDir();

	// 入力が無ければ前方向を使用
	if (VSize(dodgeDir) <= 0.1f)
	{
		dodgeDir = GetPlayer()->GetForward();
	}

	GetPlayer()->SetExternalVelocity(
		VScale(dodgeDir, GetPlayer()->GetParam().dodgeSpeed)
	);

	GetPlayer()->SetExtraHitRadius(GetPlayer()->GetParam().extraHitRadius);
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
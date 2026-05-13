#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerAttackState.h"
#include "Time.h"

void PlayerAttackState::OnStart()
{
	VECTOR attackDir = GetPlayer()->GetMoveDir();

	// 入力が無ければ前方向を使用
	if (VSize(attackDir) <= 0.1f)
	{
		attackDir = GetPlayer()->GetForward();
	}

	GetPlayer()->SetExternalVelocity(
		VScale(attackDir, GetPlayer()->GetParam().attackSpeed)
	);
}

void PlayerAttackState::OnUpdate()
{
	attackTimer += Time::GetInstance().GetDeltaTime();

	// 回避時間が経過したらステート変更
	if (attackTimer >=
		GetPlayer()->GetParam().dodgeTime)
	{
		// スティック操作の有無で Walk or Idle
		if (Input::GetInput().GetIsMoveLStick())
		{
			// Walk
			auto state = std::make_shared<PlayerWalkState>();
			GetPlayer()->ChangeState(state);
		}
		else
		{
			// Idle
			auto state = std::make_shared<PlayerIdleState>();
			GetPlayer()->ChangeState(state);
		}
	}
}

void PlayerAttackState::OnExit()
{

}
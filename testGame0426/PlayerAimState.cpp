#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerAimState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerFireState.h"
#include "Enemy.h"
#include "Time.h"

void PlayerAimState::OnStart()
{
	GetPlayer()->SetIsAim(true);
}

void PlayerAimState::OnUpdate()
{
	GetPlayer()->MoveInput();

    VECTOR inputDir = GetPlayer()->GetInputDir();

	//--------------------------------
	// Aimアニメ切り替え
	//--------------------------------

    if (VSize(inputDir) > 0.1f)
    {
        VECTOR forward = GetPlayer()->GetForward();
        forward.y = 0.0f;
        forward = VNorm(forward);

        VECTOR right =
            VCross(
                VGet(0, 1, 0),
                forward
            );

        right = VNorm(right);

        float forwardDot =
            VDot(inputDir, forward);

        float rightDot =
            VDot(inputDir, right);

        //--------------------------------
        // 前後どちらが強いか
        //--------------------------------

        if (fabs(forwardDot) > fabs(rightDot))
        {
            // 前
            if (forwardDot > 0.0f)
            {
                GetPlayer()->PlayAnimation(
                    (int)PlayerAnimState::AimWalkFront,
                    true
                );
            }
            // 後
            else
            {
                GetPlayer()->PlayAnimation(
                    (int)PlayerAnimState::AimWalkBack,
                    true
                );
            }
        }
        else
        {
            // 右
            if (rightDot > 0.0f)
            {
                GetPlayer()->PlayAnimation(
                    (int)PlayerAnimState::AimWalkRight,
                    true
                );
            }
            // 左
            else
            {
                GetPlayer()->PlayAnimation(
                    (int)PlayerAnimState::AimWalkLeft,
                    true
                );
            }
        }
    }
    else
    {
        GetPlayer()->PlayAnimation(
            (int)PlayerAnimState::Aim,
            true
        );
    }

	auto target = GetPlayer()->GetTarget().lock();

	if (!target ||
		target->IsDead())
	{
		GetPlayer()->SetIsAim(false);

		auto state =
			std::make_shared<PlayerIdleState>();

		GetPlayer()->ChangeState(state);

		return;
	}
	
	// 左トリガーが離されたらステート変更
	if ( 
		Input::GetInput().GetLeftTrigger()
		< GetPlayer()->GetParam().aimTriggerDeadZone)
	{
		GetPlayer()->SetIsAim(false);

		// Walk
		if (Input::GetInput().GetIsMoveLStick())
		{
			auto state = std::make_shared<PlayerWalkState>();
			GetPlayer()->ChangeState(state);
			return;
		}
		// Idle
		else
		{
			auto state = std::make_shared<PlayerIdleState>();
			GetPlayer()->ChangeState(state);
			return;
		}
	}

	// 右トリガーが押されたら射撃
	if (Input::GetInput().GetRightTrigger() > GetPlayer()->GetParam().fireTriggerDeadZone)
	{
		if (GetPlayer()->GetCurrentBulletNum() > 0)
		{
			auto state = std::make_shared<PlayerFireState>();
			GetPlayer()->ChangeState(state);
			return;
		}
	}
}

void PlayerAimState::OnExit()
{
}
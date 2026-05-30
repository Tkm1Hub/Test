#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerBlockState.h"
#include "PlayerAimState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerFireState.h"
#include "Enemy.h"
#include "Time.h"

void PlayerBlockState::OnStart()
{
    parryTimer = 0.0f;

    GetPlayer()->PlayAnimation((int)(PlayerAnimState::BlockIdle), false);
}

void PlayerBlockState::OnUpdate()
{
    parryTimer +=
        Time::GetInstance().GetScaledDeltaTime();

    auto target = GetPlayer()->GetTarget().lock();

    if (target)
    {
        VECTOR targetDir = VSub(
            target->GetPosition(),
            GetPlayer()->GetPosition()
        );

        targetDir.y = 0;

        targetDir = VNorm(targetDir);

        GetPlayer()->SetLookDir(targetDir);
    }

    // Lが離されたらステート変更
    if (!Input::GetInput().IsPress(XINPUT_BUTTON_LEFT_SHOULDER))
    {
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
}

void PlayerBlockState::OnExit()
{
}
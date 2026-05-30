#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerParryState.h"
#include "PlayerAimState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerFireState.h"
#include "Enemy.h"
#include "Time.h"

void PlayerParryState::OnStart()
{
    parryTimer = 0.0f;

    GetPlayer()->PlayAnimation((int)(PlayerAnimState::Parry), false);

    Time::GetInstance().SetTimeScale(0.05f);

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
        GetPlayer()->SetExternalVelocity(
            VScale(
                VScale(
                    targetDir, -1), 35)
        );
    }

}

void PlayerParryState::OnUpdate()
{
    parryTimer +=
        Time::GetInstance().GetDeltaTime();

    float t =
        parryTimer / parryTime;

    t = std::clamp(
        t,
        0.0f,
        1.0f
    );

    //---------------------------------
    // EaseInQuad
    //---------------------------------

    float ease = t * t * t;

    float timeScale =
        0.2f +
        (1.0f - 0.2f) * ease;

    Time::GetInstance().SetTimeScale(timeScale);

    // ŽžŠÔŒo‰ß‚ÅŒ³‚É–ß‚·
    if (parryTimer >= parryTime)
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

void PlayerParryState::OnExit()
{
}
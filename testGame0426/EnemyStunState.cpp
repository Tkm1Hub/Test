#include "stdafx.h"
#include "EnemyStunState.h"
#include "EnemyChaseState.h"
#include "Enemy.h"
#include "Time.h"

void EnemyStunState::OnStart()
{
    auto enemy = GetEnemy();

    if (!enemy)
        return;

    // ˆÚ“®’â~
    enemy->SetMoveVelocity(
        VGet(0, 0, 0)
    );
}

void EnemyStunState::OnUpdate()
{
    auto enemy = GetEnemy();

    if (!enemy)
        return;

    timer +=
        Time::GetInstance().GetScaledDeltaTime()
        * 60.0f;

    // ƒXƒ^ƒ“I—¹
    if (timer >= enemy->GetParam().stunTime)
    {
        auto state =
            std::make_shared<EnemyChaseState>();

        enemy->ChangeState(state);
    }
}

void EnemyStunState::OnExit()
{
    auto enemy = GetEnemy();

    if (!enemy) return;
    enemy->RecoverStun(
        enemy->GetMaxStunGauge()
    );
}
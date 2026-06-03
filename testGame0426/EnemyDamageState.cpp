#include "stdafx.h"
#include "EnemyDamageState.h"
#include "EnemyDeadState.h"
#include "EnemyCombatIdleState.h"
#include "EnemyStunState.h"
#include "Enemy.h"
#include "Time.h"

void EnemyDamageState::OnStart()
{
}

void EnemyDamageState::OnUpdate()
{
    auto enemy = GetEnemy();
    if (!enemy) return;

    timer +=
        Time::GetInstance().GetScaledDeltaTime()
        * 60.0f;

    // 被弾終了
    if (timer >= enemy->GetParam().damageTime)
    {
        //--------------------------------
                // まだスタン中
                //--------------------------------
        if (enemy->GetIsStun())
        {
            auto state =
                std::make_shared<EnemyStunState>();

            enemy->ChangeState(state);

            return;
        }

        //--------------------------------
        // 通常復帰
        //--------------------------------
        auto state =
            std::make_shared<EnemyCombatIdleState>();

        enemy->ChangeState(state);

        return;
    }
}

void EnemyDamageState::OnExit()
{
}
#include "stdafx.h"
#include "EnemyDamageState.h"
#include "EnemyDeadState.h"
#include "EnemyCombatIdleState.h"
#include "EnemyStunState.h"
#include "Enemy.h"
#include "Time.h"
#include "DamageTextUI.h"
#include "UIContainer.h"

void EnemyDamageState::OnStart()
{
    auto enemy = GetEnemy();
    if (!enemy) return;

    // 被弾情報取得
    const DamageInfo& info =
        enemy->GetLastDamageInfo();

    // ダメージUI
    auto damageUI =
        std::make_shared<DamageTextUI>();

    damageUI->Init(
        enemy->GetCapsuleTop(),
        info.damage
    );

    UIContainer::GetInstance().Add(damageUI);

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
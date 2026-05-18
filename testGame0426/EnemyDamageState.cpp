#include "stdafx.h"
#include "EnemyDamageState.h"
#include "EnemyDeadState.h"
#include "EnemyCombatIdleState.h"
#include "EnemyStunState.h"
#include "Enemy.h"
#include "Time.h"

void EnemyDamageState::OnStart()
{
    auto enemy = GetEnemy();
    if (!enemy) return;

    // 被弾情報取得
    const DamageInfo& info =
        enemy->GetLastDamageInfo();

    // ダメージ
    enemy->TakeDamage(info.damage);
    enemy->AddStunGauge(info.stunPower);

    // ノックバック
    enemy->SetExternalVelocity(
        VScale(
            info.hitDir,
            info.knockBackPower
        )
    );

    // 死亡
    if (enemy->GetHP() <= 0)
    {
        auto state = std::make_shared<EnemyDeadState>();
        enemy->ChangeState(state);
        return;
    }


    // 地面解除
    enemy->SetIsGraund(false);

    // 移動停止
    enemy->SetMoveVelocity(
        VGet(0, 0, 0)
    );
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
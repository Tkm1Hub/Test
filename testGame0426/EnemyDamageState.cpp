#include "stdafx.h"
#include "EnemyDamageState.h"
#include "EnemyDeadState.h"
#include "EnemyChaseState.h"
#include "Enemy.h"
#include "Time.h"

void EnemyDamageState::OnStart()
{
    auto enemy = GetEnemy();
    if (!enemy) return;

    // ”í’eî•ñŽæ“¾
    const DamageInfo& info =
        enemy->GetLastDamageInfo();

    // ƒ_ƒ[ƒW
    enemy->TakeDamage(info.damage);

    // ƒmƒbƒNƒoƒbƒN
    enemy->SetExternalVelocity(
        VScale(
            info.hitDir,
            info.knockBackPower
        )
    );

    // Ž€–S
    if (enemy->GetHP() <= 0)
    {
        auto state = std::make_shared<EnemyDeadState>();
        enemy->ChangeState(state);
        return;
    }


    // ’n–Ê‰ðœ
    enemy->SetIsGraund(false);

    // ˆÚ“®’âŽ~
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

    // ”í’eI—¹
    if (timer >= enemy->GetParam().damageTime)
    {
        auto state = std::make_shared<EnemyChaseState>();
        enemy->ChangeState(state);
        return;
    }
}

void EnemyDamageState::OnExit()
{

}
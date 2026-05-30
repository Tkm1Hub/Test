#include "stdafx.h"
#include "EnemyStunState.h"
#include "EnemyCombatIdleState.h"
#include "Enemy.h"
#include "EffectContainer.h"
#include "Time.h"

void EnemyStunState::OnStart()
{
}

void EnemyStunState::OnUpdate()
{
    auto enemy = GetEnemy();

    if (!enemy)
        return;

    // ƒXƒ^ƒ“I—¹
    if (!enemy->GetIsStun())
    {
        auto state =
            std::make_shared<EnemyCombatIdleState>();

        enemy->ChangeState(state);

        return;
    }
}

void EnemyStunState::OnExit()
{
}
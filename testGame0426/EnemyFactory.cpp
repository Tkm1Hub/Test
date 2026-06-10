#include "stdafx.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "EnemyMelee.h"
#include "EnemyShooter.h"
#include "Objects.h"

void EnemyFactory::Init()
{
    modelHandles[EnemyType::Melee]
        = MV1LoadModel("data/model/EnemyMelee.mv1");

    modelHandles[EnemyType::Shooter]
        = MV1LoadModel("data/model/EnemyShooter.mv1");
}

void EnemyFactory::Create(
    EnemyType type,
    std::weak_ptr<Player> player,
    const VECTOR& pos)
{
    std::shared_ptr<Enemy> enemy;

    switch (type)
    {
    case EnemyType::Melee:

        enemy = std::make_shared<EnemyMelee>();
        break;

    case EnemyType::Shooter:

        enemy = std::make_shared<EnemyShooter>();
        break;
    }

    enemy->SetBaseModelHandle(modelHandles[type]);

    Objects::GetInstance().Add(enemy);

    enemy->SetPlayer(player);

    enemy->SetPosition(pos);
}
#pragma once
#include "EnemyStateBase.h"

class EnemyDamageState : public EnemyStateBase
{
public:
    void OnStart() override;
    void OnUpdate() override;
    void OnExit() override;

private:
    float timer = 0.0f;
};
#pragma once
#include "EnemyStateBase.h"

class EnemyStunState : public EnemyStateBase
{
public:
    void OnStart() override;
    void OnUpdate() override;
    void OnExit() override;

    const char* GetName() const override
    {
        return "Stun";
    }
private:
    float timer = 0.0f;
};
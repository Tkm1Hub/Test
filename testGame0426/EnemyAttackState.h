#pragma once
#include "EnemyStateBase.h"
#include "AttackData.h"

class EnemyAttackState : public EnemyStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	int currentStep = 0;
	float timer = 0.0f;
	AttackPhase phase = AttackPhase::Windup;
	bool hasHit = false;
};
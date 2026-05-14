#pragma once
#include "PlayerStateBase.h"

class PlayerAttackState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	int currentStep = 0;
	float timer = 0.0f;
	AttackPhase phase = AttackPhase::Active;
	bool hasHit = false;
};
#pragma once
#include "PlayerStateBase.h"

class PlayerAttackState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Attack";
	}
private:
	int currentStep = 0;
	float timer = 0.0f;
	AttackPhase phase = AttackPhase::Windup;
	bool hasHit = false;
	bool nextComboRequested = false;
};
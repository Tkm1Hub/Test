#pragma once
#include "PlayerStateBase.h"

class PlayerSPAttackState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "SPAttack";
	}
private:
	int currentStep = 0;
	float timer = 0.0f;
	AttackPhase phase = AttackPhase::Windup;
	bool hasHit = false;
	bool nextComboRequested = false;

	void PlayAttackAnimation(int step);
};
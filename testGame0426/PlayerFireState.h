#pragma once
#include "PlayerStateBase.h"

class PlayerFireState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Fire";
	}
private:
	float fireTimer = 0.0f;
	float fireTime = 0.35f;
	AttackPhase phase = AttackPhase::Windup;
	bool hasHit = false;
};
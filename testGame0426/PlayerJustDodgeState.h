#pragma once
#include "PlayerStateBase.h"

class PlayerJustDodgeState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "JustDodge";
	}

private:
	float justDodgeTimer = 0.0f;
	float justDodgeTime = 0.5f;
};
#pragma once
#include "PlayerStateBase.h"

class PlayerDodgeState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Dodge";
	}
private:
	float dodgeTimer = 0.0f;
	float dodgeTime = 1.0f;
};
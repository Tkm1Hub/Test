#pragma once
#include "PlayerStateBase.h"

class PlayerAimState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Aim";
	}

private:
	float TRIGGER_DEADZONE = 100;
};
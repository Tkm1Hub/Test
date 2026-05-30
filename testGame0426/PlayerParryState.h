#pragma once
#include "PlayerStateBase.h"

class PlayerParryState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Parry";
	}

private:
	float parryTimer = 0.0f;

	float parryTime = 0.75f;
};
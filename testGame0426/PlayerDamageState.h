#pragma once
#include "PlayerStateBase.h"

class PlayerDamageState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Damage";
	}
private:
	float timer = 0.0f;
};
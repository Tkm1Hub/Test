#pragma once
#include "PlayerStateBase.h"

class PlayerIdleState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Idle";
	}
};
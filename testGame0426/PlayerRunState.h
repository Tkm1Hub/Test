#pragma once
#include "PlayerStateBase.h"

class PlayerRunState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Run";
	}
};
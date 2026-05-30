#pragma once
#include "PlayerStateBase.h"

class PlayerBlockState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Block";
	}

	bool IsParryWindow() const
	{
		return parryTimer <= parryWindow;
	}
private:
	float parryTimer = 0.0f;

	float parryWindow = 0.15f;
};
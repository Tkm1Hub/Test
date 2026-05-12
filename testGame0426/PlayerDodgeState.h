#pragma once
#include "PlayerStateBase.h"

class PlayerDodgeState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	float dodgeTimer = 0.0f;
	float dodgeTime = 0.35f;
};
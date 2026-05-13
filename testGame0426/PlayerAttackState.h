#pragma once
#include "PlayerStateBase.h"

class PlayerAttackState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	float attackTimer = 0.0f;
	float dodgeTime = 0.35f;
};
#pragma once
#include "PlayerStateBase.h"

class PlayerDodgeState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};
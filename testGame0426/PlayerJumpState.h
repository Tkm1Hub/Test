#pragma once
#include "PlayerStateBase.h"

class PlayerJumpState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};
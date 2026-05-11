#pragma once
#include "PlayerStateBase.h"

class PlayerFallState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};
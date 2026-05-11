#pragma once
#include "PlayerStateBase.h"

class PlayerWalkState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};
#pragma once
#include "StateBase.h"
#include "Player.h"

class PlayerStateBase : public StateBase
{
protected:

	Player* GetPlayer()
	{
		return static_cast<Player*>(Owner);
	}
};
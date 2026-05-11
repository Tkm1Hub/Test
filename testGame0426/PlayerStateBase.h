#pragma once
#include "StateBase.h"

class Player;
class PlayerStateBase : public StateBase
{
public:
	void SetOwner(Player* a_pPlayer)
	{
		player = a_pPlayer;
	}

protected:
	Player* player = nullptr;
};
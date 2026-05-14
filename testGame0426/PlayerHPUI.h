#pragma once
#include "UIBase.h"

class Player;
class PlayerHPUI : public UIBase
{
public:
	void SetPlayer(Player* player);

	void Draw() override;

private:
	Player* player = nullptr;
};
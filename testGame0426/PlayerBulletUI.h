#pragma once
#include "UIBase.h"
class Player;

class PlayerBulletUI:public UIBase
{
public:
	void SetPlayer(Player* player);

	void Draw();

private:
	Player* player = nullptr;

	int bulletWidth = 40;
	int bulletHeight = 40;
	int bulletSpace = 12;

	int startX = 50;
	int startY = 950;
};
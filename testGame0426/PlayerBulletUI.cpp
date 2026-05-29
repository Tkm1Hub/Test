#include "stdafx.h"
#include "PlayerBulletUI.h"
#include "Player.h"

void PlayerBulletUI::SetPlayer(Player* player)
{
	this->player = player;
}

void PlayerBulletUI::Draw()
{
	if (!player) return;

	//--------------------------------
	// Œ»Ý’e”
	//--------------------------------

	int currentBullet =
		player->GetCurrentBulletNum();

	//--------------------------------
	// Å‘å’e”
	//--------------------------------

	int maxBullet =
		player->GetParam().BulletNum;

	//--------------------------------
	// •`‰æ
	//--------------------------------

	for (int i = 0; i < maxBullet; i++)
	{
		int x =
			startX +
			(bulletWidth + bulletSpace) * i;

		int y = startY;

		//--------------------------------
		// ŠŽ‚µ‚Ä‚¢‚é’e
		//--------------------------------

		bool hasBullet =
			i < currentBullet;

		unsigned int insideColor;

		if (hasBullet)
		{
			insideColor =
				GetColor(120, 255, 80);
		}
		else
		{
			insideColor =
				GetColor(40, 40, 40);
		}

		//--------------------------------
		// ŠO˜g
		//--------------------------------

		DrawRoundRect(
			x,
			y,
			x + bulletWidth,
			y + bulletHeight,
			15,
			15,
			GetColor(255, 180, 0),
			TRUE
		);

		//--------------------------------
		// “à‘¤
		//--------------------------------

		DrawRoundRect(
			x + 4,
			y + 4,
			x + bulletWidth - 4,
			y + bulletHeight - 4,
			12,
			12,
			insideColor,
			TRUE
		);

		//--------------------------------
		// ŠO‘¤ƒ‰ƒCƒ“
		//--------------------------------

		DrawRoundRect(
			x,
			y,
			x + bulletWidth,
			y + bulletHeight,
			15,
			15,
			GetColor(255, 220, 0),
			FALSE
		);
	}
}
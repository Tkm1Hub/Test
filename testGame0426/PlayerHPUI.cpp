#include "PlayerHPUI.h"
#include "Player.h"

void PlayerHPUI::SetPlayer(Player* player)
{
    this->player = player;
}

void PlayerHPUI::Draw()
{
    if (!player) return;

    int hp = player->GetHP();
    int maxHp = player->GetMaxHP();

    float rate =
        static_cast<float>(hp) / maxHp;

    int width = 400;
    int height = 30;

    int x = 50;
    int y = 1000;

    // òg
    DrawBox(
        x,
        y,
        x + width,
        y + height,
        GetColor(255, 255, 255),
        FALSE
    );

    // íÜêg
    DrawBox(
        x,
        y,
        x + static_cast<int>(width * rate),
        y + height,
        GetColor(0, 255, 0),
        TRUE
    );
}
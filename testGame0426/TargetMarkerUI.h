#pragma once
#include "UIBase.h"

class Player;

class TargetMarkerUI : public UIBase
{
public:
    void SetPlayer(Player* player);

    void Update() override;
    void Draw() override;

private:
    Player* player = nullptr;

    int effectHandle = -1;

    bool isPlaying = false;
};
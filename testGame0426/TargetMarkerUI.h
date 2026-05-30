#pragma once
#include "UIBase.h"

class Player;
class Enemy;
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

    Enemy* currentTarget = nullptr;

    std::string currentEffectName;
};
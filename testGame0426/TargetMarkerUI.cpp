#include "stdafx.h"
#include "TargetMarkerUI.h"
#include "Player.h"
#include "Enemy.h"
#include "EffectContainer.h"

void TargetMarkerUI::SetPlayer(Player* playerPtr)
{
    player = playerPtr;
}

void TargetMarkerUI::Update()
{
    if (!player) return;

    auto target = player->GetTarget().lock();

    //-----------------------------------
    // ターゲットなし
    //-----------------------------------

    if (!target)
    {
        if (isPlaying)
        {
            StopEffekseer2DEffect(effectHandle);

            effectHandle = -1;
            isPlaying = false;
        }

        return;
    }

    //-----------------------------------
    // ワールド座標 → スクリーン座標
    //-----------------------------------

    VECTOR worldPos =
        target->GetCapsuleCenter();

    VECTOR screenPos =
        ConvWorldPosToScreenPos(worldPos);

    //-----------------------------------
    // カメラの後ろ
    //-----------------------------------

    if (screenPos.z < 0.0f)
    {
        return;
    }

    //-----------------------------------
    // 初回再生
    //-----------------------------------

    if (!isPlaying)
    {
        effectHandle =
            PlayEffekseer2DEffect(
                EffectContainer::GetInstance()
                .GetEffectHandle("TargetMarker")
            );

        isPlaying = true;
    }

    //-----------------------------------
    // 座標更新
    //-----------------------------------

    SetPosPlayingEffekseer2DEffect(
        effectHandle,
        screenPos.x,
        screenPos.y,
		0.0f
    );
}

void TargetMarkerUI::Draw()
{
}
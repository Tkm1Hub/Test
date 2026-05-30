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
            currentTarget = nullptr;
            currentEffectName.clear();
        }

        return;
    }

    Enemy* targetPtr = target.get();

    //-----------------------------------
    // 使用するマーカー決定
    //-----------------------------------

    std::string nextEffectName =
        player->GetIsLockOn()
        ? "LockOnMarker"
        : "TargetMarker";

    //-----------------------------------
    // 再生し直し判定
    //-----------------------------------

    bool needRestart = false;

    if (targetPtr != currentTarget)
    {
        needRestart = true;
    }

    if (nextEffectName != currentEffectName)
    {
        needRestart = true;
    }

    //-----------------------------------
    // エフェクト再生
    //-----------------------------------

    if (needRestart)
    {
        if (isPlaying)
        {
            StopEffekseer2DEffect(effectHandle);
        }

        effectHandle =
            PlayEffekseer2DEffect(
                EffectContainer::GetInstance()
                .GetEffectHandle(nextEffectName)
            );

        currentTarget = targetPtr;
        currentEffectName = nextEffectName;
        isPlaying = true;
    }

    //-----------------------------------
    // ワールド座標→スクリーン座標
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
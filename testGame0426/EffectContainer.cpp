#include "stdafx.h"
#include "EffectContainer.h"
#include "Time.h"

void EffectContainer::Init()
{
    LoadEffect("AttackReady_yellow", "data/effect/AttackReady_yellow.efkefc", 30.0f);
}

/// <summary>
/// 初期化
/// </summary>
void EffectContainer::LoadEffect(const std::string& name, const std::string& path, float magnification)
{
    if (effectHandles.find(name) == effectHandles.end()) {
        int handle = LoadEffekseerEffect(path.c_str(), magnification);
        effectHandles[name] = handle;
    }
}

void EffectContainer::PositionUpdate(const VECTOR& objectPosition)
{
    position = VGet(objectPosition.x, objectPosition.y, objectPosition.z);


    // 再生中のエフェクトを移動する。
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);

}

/// <summary>
/// 更新
/// </summary>
void EffectContainer::Update()
{
    float timeScale = Time::GetInstance().GetTimeScale();

    // 再生中のエフェクト全てにスピードを反映
    for (auto& e : activeEffects)
    {
        if (e.isActive)
        {
            SetSpeedPlayingEffekseer3DEffect(e.handle, timeScale);
        }
    }

    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();
}

/// <summary>
/// 描画
/// </summary>
void EffectContainer::Draw()
{
    // Effekseerにより再生中のエフェクトを描画する。
    //DrawEffekseer3D_Draw(playingEffectHandle);
    DrawEffekseer3D();

}

/// <summary>
/// ポジションを保存
/// </summary>
/// <param name="setPosition"></param>
void EffectContainer::SetPosition(const std::string& name, const VECTOR setPosition)
{
    // エフェクトの位置を更新
    for (auto& e : activeEffects) {
        if (e.name == name && e.isActive) {
            SetPosPlayingEffekseer3DEffect(e.handle,
                setPosition.x,
                setPosition.y,
                setPosition.z);
            e.position = setPosition;
        }
    }
}

/// <summary>
/// 拡大率
/// </summary>
/// <param name="scale"></param>
void EffectContainer::SetScale(VECTOR scale)
{
    SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);
}

/// <summary>
///  エフェクトを再生
/// </summary>
void EffectContainer::PlayEffect(const std::string& name, const VECTOR& position)
{
    // エフェクトを再生する。
    auto it = effectHandles.find(name);
    if (it == effectHandles.end()) return;

    int handle = PlayEffekseer3DEffect(it->second);
    SetPosPlayingEffekseer3DEffect(handle, position.x, position.y, position.z);

    float timeScale = Time::GetInstance().GetTimeScale();
    SetSpeedPlayingEffekseer3DEffect(handle, timeScale);

    activeEffects.push_back(EffectInstance{ name,handle, position, true });
}

/// <summary>
/// 再生中のモーションを停止する
/// </summary>
void EffectContainer::StopEffect()
{
    StopEffekseer3DEffect(playingEffectHandle);
}

void EffectContainer::SetSpeed(float speed)
{
    SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, speed);
}

/// <summary>
/// 角度
/// </summary>
/// <param name="setPosition"></param>
void EffectContainer::SetRotation(const std::string& name, VECTOR setRotation)
{
    // エフェクトの位置を更新
    for (auto& e : activeEffects) {
        if (e.name == name && e.isActive) {
            SetRotationPlayingEffekseer3DEffect(e.handle,
                setRotation.x,
                setRotation.y,
                setRotation.z);
            e.position = setRotation;
        }
    }
}
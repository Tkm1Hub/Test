#pragma once
#include <unordered_map>

class Animation
{
public:

    void LoadModel(int handle);

    void AddAnimation(int animID,int animHandle);

    void Play(int animIndex, bool loop);

    void Update();

private:

    struct AnimData
    {
        int handle;
    };

    int modelHandle = -1;

    std::unordered_map<int, int> animTable;
    int currentAnimIndex = -1;

    int currentPlayAnim = -1;
    int prevPlayAnim = -1;

    float currentAnimCount = 0.0f;
    float prevAnimCount = 0.0f;

    float animBlendRate = 1.0f;

    static constexpr float ANIM_PLAY_SPEED = 0.25f; // アニメーションの再生速度 
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // アニメーションのブレンド率変化速度

    bool isLoop = false;
    bool isAnimFinished = false;
};
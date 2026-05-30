#pragma once
struct EffectInstance
{
    std::string name;
    int handle = -1;
    VECTOR position;
    bool isActive = false;
	bool isLoop = false;
};


class EffectContainer
{
private:
    // コンストラクタを非公開にする
    EffectContainer() {}

    // コピーコンストラクタと代入演算子を削除
    EffectContainer(const EffectContainer&) = delete;
    EffectContainer& operator=(const EffectContainer&) = delete;

    ~EffectContainer() {}

    VECTOR position = { 0.0f,0.0f,0.0f };
    int time = 0;
    int playingEffectHandle = -1;
    int resourceHandle = -1;
    std::unordered_map<std::string, int> effectHandles;
    std::vector<EffectInstance> activeEffects;

public:
    // インスタンスを取得
    static EffectContainer& GetInstance()
    {
        static EffectContainer instance;
        return instance;
    }

    void Init();
    void LoadEffect(const std::string& name, const std::string& path, float magnification);
    void PositionUpdate(const VECTOR& objectPosition);
    void Update();
    void Draw();
    void SetScale(VECTOR scale);
    void SetSpeed(float speed);
    void SetPosition(const std::string& name, const VECTOR setPosition);
    void SetRotation(const std::string& name, VECTOR setPosition);
    int PlayEffect(const std::string& name, const VECTOR& position, bool loop);
    void StopEffect(const std::string& name);

    int GetEffectHandle(const std::string& name);
};


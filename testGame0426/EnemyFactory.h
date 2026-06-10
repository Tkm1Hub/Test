#pragma once
#include <memory>
#include <unordered_map>

enum class EnemyType
{
    Melee,
    Shooter,
};

class Player;

class EnemyFactory
{
private:
    // コンストラクタを非公開にする
    EnemyFactory() {}

    // コピーコンストラクタと代入演算子を削除
    EnemyFactory(const EnemyFactory&) = delete;
    EnemyFactory& operator=(const EnemyFactory&) = delete;

    ~EnemyFactory() {}
public:
    // インスタンスを取得
    static EnemyFactory& GetInstance()
    {
        static EnemyFactory instance;
        return instance;
    }

    void Init();

    void Create(
        EnemyType type,
        std::weak_ptr<Player> player,
        const VECTOR& pos
    );

private:

    std::unordered_map<EnemyType, int> modelHandles;
};
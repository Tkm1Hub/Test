#pragma once
#include <unordered_set>

class Enemy;
class AttackToken
{
private:
    //コンストラクタを非公開にする
    AttackToken() {}

    // コピーコンストラクタと代入演算子を削除
    AttackToken(const AttackToken&) = delete;
    AttackToken& operator=(const AttackToken&) = delete;

    //プライベートデストラクタ
    ~AttackToken() {}
public:
    // インスタンスを取得するためのメソッド
    static AttackToken& GetInstance()
    {
        static AttackToken instance;      // 静的変数としてインスタンスを定義
        return instance;
    }

    bool RequestToken(Enemy* enemy);

    void ReleaseToken(Enemy* enemy);

    bool HasToken(Enemy* enemy);

private:
    std::unordered_set<Enemy*> attackers;

    int maxAttackers = 2;   // 最大攻撃権数
};
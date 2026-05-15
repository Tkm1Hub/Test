#pragma once
#include <vector>
#include <memory>

class UIBase;
class UIManager
{
private:
    //コンストラクタを非公開にする
    UIManager() {}

    // コピーコンストラクタと代入演算子を削除
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    //プライベートデストラクタ
    ~UIManager() {}
public:
    // インスタンスを取得するためのメソッド
    static UIManager& GetInstance()
    {
        static UIManager instance;      // 静的変数としてインスタンスを定義
        return instance;
    }

    void Add(std::shared_ptr<UIBase> ui);

    void Update();
    void Draw();

private:
    std::vector<std::shared_ptr<UIBase>>uiList;
    std::vector<std::shared_ptr<UIBase>>pendingUiList;
};
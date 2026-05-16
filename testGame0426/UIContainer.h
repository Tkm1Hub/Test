#pragma once
#include <vector>
#include <memory>

class UIBase;
class UIContainer
{
private:
    //コンストラクタを非公開にする
    UIContainer() {}

    // コピーコンストラクタと代入演算子を削除
    UIContainer(const UIContainer&) = delete;
    UIContainer& operator=(const UIContainer&) = delete;

    //プライベートデストラクタ
    ~UIContainer() {}
public:
    // インスタンスを取得するためのメソッド
    static UIContainer& GetInstance()
    {
        static UIContainer instance;      // 静的変数としてインスタンスを定義
        return instance;
    }

    void Add(std::shared_ptr<UIBase> ui);

    void Update();
    void Draw();

private:
    std::vector<std::shared_ptr<UIBase>>uiList;
    std::vector<std::shared_ptr<UIBase>>pendingUiList;
};
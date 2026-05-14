#pragma once
#include "object.h"
class Objects
{
private:
    //コンストラクタを非公開にする
    Objects() {}

    // コピーコンストラクタと代入演算子を削除
    Objects(const Objects&) = delete;
    Objects& operator=(const Objects&) = delete;

    //プライベートデストラクタ
    ~Objects() {}
public:
    // インスタンスを取得するためのメソッド
    static Objects& GetInstance()
    {
        static Objects instance;      // 静的変数としてインスタンスを定義
        return instance;
    }

	std::vector<std::shared_ptr<Object>> objects;

    // 追加予約リスト
    std::vector<std::shared_ptr<Object>> pendingObjects;

	void Add(std::shared_ptr<Object> obj);
	void Init();
	void Update();
	void Draw();
};
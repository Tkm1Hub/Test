#pragma once

#include "PlayerParameter.h"

class ParameterContainer
{
private:
    // コンストラクタを非公開にする
    ParameterContainer() {}

    // コピーコンストラクタと代入演算子を削除
    ParameterContainer(const ParameterContainer&) = delete;
    ParameterContainer& operator=(const ParameterContainer&) = delete;

    ~ParameterContainer() {}

public:
    // インスタンスを取得
    static ParameterContainer& GetInstance()
    {
        static ParameterContainer instance;
        return instance;
    }

    void Load();

    const PlayerParameter& GetPlayerParameter() const
    {
        return playerParameter;
    }

private:
    PlayerParameter playerParameter;
};
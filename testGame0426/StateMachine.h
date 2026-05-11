#pragma once
#include <iostream>
#include "StateBase.h"
class StateMachine
{
public:
	// ステートを変更する
	void ChangeState(std::shared_ptr<StateBase> newState)
	{
		// すでにステートがセットされていたら終了
		if (nowState != nullptr)
		{
			nowState->OnExit();
			nowState = nullptr;
		}

		// 新しいステートをセットする
		nowState = newState;

		// 新しいステートを開始する
		nowState->OnStart();
	}

	// 更新関数
	void Update()
	{
		if (nowState != nullptr)
		{
			nowState->OnUpdate();
		}
	}

private:
	std::shared_ptr<StateBase> nowState = nullptr;
};
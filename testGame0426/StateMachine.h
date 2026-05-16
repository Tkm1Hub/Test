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
		if (currentState != nullptr)
		{
			currentState->OnExit();
			currentState = nullptr;
		}

		// 新しいステートをセットする
		currentState = newState;

		// 新しいステートを開始する
		currentState->OnStart();
	}

	// 更新関数
	void Update()
	{
		if (currentState != nullptr)
		{
			currentState->OnUpdate();
		}
	}

	// 現在のステートを取得
	StateBase* GetCurrentState() const
	{
		return currentState.get();
	}

private:
	std::shared_ptr<StateBase> currentState = nullptr;
};
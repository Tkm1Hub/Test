#pragma once
#include "DamageInfo.h"

class StunComponent
{
public:

	float GetStunGauge() const
	{
		return stunGauge;
	}

	float GetMaxStunGauge() const
	{
		return maxStunGauge;
	}

	bool GetIsStun() const
	{
		return isStun;
	}

	// スタン加算
	void AddStunGauge(float value)
	{
		// スタン中は加算しない
		if (isStun)
			return;

		stunGauge += value;

		if (stunGauge >= maxStunGauge)
		{
			stunGauge = maxStunGauge;

			StartStun();
		}
	}

	// スタン開始
	void StartStun()
	{
		isStun = true;

		stunTimer = stunTime;

		OnStun();
	}

	// スタン更新
	void UpdateStun(float deltaTime)
	{
		// スタン中
		if (isStun)
		{
			stunTimer -= deltaTime;

			// タイマー割合
			float rate =
				stunTimer / stunTime;

			rate = std::max(0.0f, std::min(rate, 1.0f));

			// 見た目ゲージ更新
			stunGauge =
				maxStunGauge * rate;

			// 終了
			if (stunTimer <= 0.0f)
			{
				stunTimer = 0.0f;

				stunGauge = 0.0f;

				isStun = false;
			}
		}
	}

	virtual void OnStun() = 0;

protected:

	float stunGauge = 0.0f;
	float maxStunGauge = 100.0f;
	bool isStun = false;
	float stunTimer = 0.0f;
	float stunTime = 180.0f;
	float normalRecoverSpeed = 8.0f;

	DamageInfo lastStunInfo;
};
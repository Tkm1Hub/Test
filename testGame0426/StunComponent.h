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

	float GetStunTimer() const
	{
		return stunTimer;
	}

	//--------------------------------
	// スタン加算
	//--------------------------------
	void AddStunGauge(float value)
	{
		if (isStun) return;
		
		stunGauge += value;

		if (stunGauge >= maxStunGauge)
		{
			stunGauge = maxStunGauge;

			// まだスタンしていない時だけ
			if (!isStun)
			{
				StartStun();
			}
		}
	}

	//--------------------------------
	// スタン回復
	//--------------------------------
	void RecoverStun(float value)
	{
		stunGauge -= value;

		if (stunGauge < 0.0f)
		{
			stunGauge = 0.0f;
		}
	}

	//--------------------------------
	// スタン開始
	//--------------------------------
	void StartStun()
	{
		isStun = true;

		stunTimer = stunTime;

		OnStun();
	}

	//--------------------------------
	// スタン更新
	//--------------------------------
	void UpdateStun(float deltaTime)
	{
		if (!isStun)
			return;

		stunTimer -= deltaTime;

		if (stunTimer <= 0.0f)
		{
			stunTimer = 0.0f;

			isStun = false;

			stunGauge = 0.0f;
		}
	}

	virtual void OnStun() = 0;

protected:

	float stunGauge = 0.0f;

	float maxStunGauge = 100.0f;

	bool isStun = false;

	float stunTimer = 0.0f;

	float stunTime = 120.0f;

	DamageInfo lastStunInfo;
};
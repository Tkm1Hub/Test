#pragma once
#pragma once
#include <memory>

#include "Object.h"
#include "DamageInfo.h"

class StunComponent
{
public:
	float GetStunGauge() const { return stunGauge; }

	float GetMaxStunGauge() const { return maxStunGauge; }

	void AddStunGauge(float value)
	{
		stunGauge += value;
		if (stunGauge > maxStunGauge)
		{
			stunGauge = maxStunGauge;

		}
	}

	void RecoverStun(int value)
	{
		stunGauge -= value;

		if (stunGauge < 0)
		{
			stunGauge = 0;
		}
	}

	virtual void OnStun() const = 0;

	bool GetIsStun() 
	{
		return stunGauge >= maxStunGauge;
	}

protected:
	float stunGauge = 0;
	float maxStunGauge = 0;
	DamageInfo lastStunInfo;
};
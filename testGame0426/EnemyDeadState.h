#pragma once
#include "EnemyStateBase.h"

class EnemyDeadState : public EnemyStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Dead";
	}
private:
	float timer = 0.0f;

	// €–SŒã‚ÉÁ‚¦‚é‚Ü‚Å‚ÌŠÔ
	float destroyTime = 2.0f;
};
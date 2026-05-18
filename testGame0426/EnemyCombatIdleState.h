#pragma once
#include "EnemyStateBase.h"

class EnemyCombatIdleState : public EnemyStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "CombatIdle";
	}
};
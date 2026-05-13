#pragma once
#include "EnemyStateBase.h"

class EnemyAttackState : public EnemyStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};
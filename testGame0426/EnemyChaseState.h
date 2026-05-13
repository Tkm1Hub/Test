#pragma once
#include "EnemyStateBase.h"

class EnemyChaseState : public EnemyStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};
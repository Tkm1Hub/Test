#pragma once
#include "EnemyStateBase.h"

class EnemyChaseState : public EnemyStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Chase";
	}
};
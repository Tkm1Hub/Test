#pragma once
#include "Enemy.h"
#include "EnemyMeleeParameter.h"
#include "AttackData.h"

class EnemyMelee :public Enemy
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void Attack(const AttackStep& step) override;

	const EnemyParameter& GetParam() const override { return param; }

	const EnemyMeleeParameter& GetEnemyMeleeParam() { return param; }

private:
	EnemyMeleeParameter param;
};
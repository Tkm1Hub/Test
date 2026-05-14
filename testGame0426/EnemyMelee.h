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

	float GetAttackRange() const { return param.attackRange; }

	const EnemyMeleeParameter& GetParam() { return param; }
private:
	EnemyMeleeParameter param;
};
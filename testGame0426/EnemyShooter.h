#pragma once
#include "Enemy.h"
#include "EnemyShooterParameter.h"
#include "AttackData.h"

class EnemyShooter :public Enemy
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void Attack(const AttackStep& step) override;

	void Chase() override;

	const EnemyParameter& GetParam() const override { return param; }

	const EnemyShooterParameter& GetEnemyMeleeParam() { return param; }

private:
	EnemyShooterParameter param;
};
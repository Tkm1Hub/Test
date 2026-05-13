#pragma once
#include "Enemy.h"
#include "EnemyMeleeParameter.h"

class EnemyMelee :public Enemy
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void Attack() override;

	const EnemyMeleeParameter& GetParam() { return param; }
private:
	EnemyMeleeParameter param;
};
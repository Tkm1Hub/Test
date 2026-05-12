#pragma once
#include "Enemy.h"

class EnemyMelee :public Enemy
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void Attack() override;

private:

};
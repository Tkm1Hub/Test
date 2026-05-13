#include "stdafx.h"
#include "EnemyMelee.h"
#include "EnemyChaseState.h"

void EnemyMelee::Init()
{
	pos = VGet(0.0f, 0.0f, 10.0f);
	maxMoveSpeed = param.maxMoveSpeed;
	auto state = std::make_shared<EnemyChaseState>();
	ChangeState(state);
}

void EnemyMelee::Update()
{
	Enemy::Update();
}

void EnemyMelee::Draw()
{
	DrawCapsule3D(pos, VAdd(pos, VGet(0.0f, 5.0f, 0.0f)), 2.0f, 8, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);

	Object::Draw();
}

void EnemyMelee::Attack()
{

}
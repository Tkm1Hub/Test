#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

void Enemy::SetPlayer(const std::weak_ptr<Player>& playerPtr)
{
	player = playerPtr;
}

void Enemy::ChangeState(std::shared_ptr<EnemyStateBase> a_spState)
{
	a_spState->SetOwner(this);
	stateMachine.ChangeState(a_spState);
}


void Enemy::Update()
{
	// ステート更新
	stateMachine.Update();

	// 方向更新
	RotateAngle();

	// 重力適応
	ApplyGravity();

	// 速度を適用
	ApplyVelocity();
}

void Enemy::MoveTo(const VECTOR& targetPos)
{
	// 目標への方向
	VECTOR dir = VSub(targetPos, pos);

	// Y座標は無視
	dir.y = 0.0f;

	dir = VNorm(dir);

	moveDir = dir;
}

void Enemy::Chase()
{
	auto p = player.lock();
	if (!p) return;

	MoveTo(p->GetPosition());
}
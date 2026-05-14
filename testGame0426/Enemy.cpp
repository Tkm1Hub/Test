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
	moveDir = VGet(0.0f, 0.0f, 0.0f);		// 毎フレーム移動入力をリセット

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
	lookDir = moveDir;
}

void Enemy::Chase()
{
	auto p = player.lock();
	if (!p) return;

	MoveTo(p->GetPosition());
}

float Enemy::GetDistanceToPlayer() const
{
	auto p = player.lock();
	if (!p) return FLT_MAX;

	VECTOR dir = VSub(p->GetPosition(), pos);
	dir.y = 0.0f;

	return VSize(dir);
}

VECTOR Enemy::GetDirectionToPlayer()const
{
	auto p = player.lock();
	if (!p) return VGet(0.0f,0.0f,0.0f);

	VECTOR dir = VSub(p->GetPosition(), pos);
	dir.y = 0.0f;

	return VNorm(dir);
}
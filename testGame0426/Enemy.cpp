#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyDeadState.h"
#include "EnemyDamageState.h"
#include "EnemyStunState.h"
#include "EffectContainer.h"
#include "DamageTextUI.h"
#include "UIContainer.h"
#include "Time.h"

void Enemy::SetPlayer(const std::weak_ptr<Player>& playerPtr)
{
	player = playerPtr;
}

void Enemy::ChangeState(std::shared_ptr<EnemyStateBase> a_spState)
{
	a_spState->SetOwner(this);
	stateMachine.ChangeState(a_spState);
}

void Enemy::Init()
{
	team = Team::Enemy;
	maxStunGauge = GetParam().maxStunGauge;
}

void Enemy::Update()
{
	// 攻撃クールダウン
	UpdateAttackCoolDown();

	// スタン更新
	UpdateStun(Time::GetInstance().GetScaledDeltaTime() * 60.0f);

	moveDir = VGet(0.0f, 0.0f, 0.0f);		// 毎フレーム移動入力をリセット

	// ステート更新
	stateMachine.Update();

	// 方向更新
	RotateAngle();

	// 重力適応
	ApplyGravity();

	// 速度を適用
	ApplyVelocity();

	// ステージとの当たり判定
	ResolveStageCollision();

	// アニメーションの更新
	animation.Update();

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

void Enemy::OnHit(const DamageInfo& info)
{
	// 既に死亡してたら無視
	if (IsDead()) return;

	//-------------------------------
	// ダメージ計算
	//-------------------------------
	float damageRate = 1.0f;
	float stunRate = 1.0f;

	switch (info.damageType)
	{
	case DamageType::Melee:
		damageRate = GetParam().meleeDamageRate;
		stunRate = GetParam().meleeStunRate;
		break;

	case DamageType::Projectile:
		damageRate = GetParam().projectileDamageRate;
		stunRate = GetParam().prijectileStunRate;
		break;
	}

	int finalDamage = static_cast<int>(info.damage * damageRate);
	int finalStunPower = static_cast<int>(info.stunPower * stunRate);

	// 保存（UI用）
	lastDamageInfo = info;
	lastDamageInfo.damage = finalDamage;
	lastDamageInfo.stunPower = finalStunPower;

	// ダメージUI
	auto damageUI =
		std::make_shared<DamageTextUI>();

	damageUI->Init(
		GetCapsuleTop(),
		info.damage
	);

	UIContainer::GetInstance().Add(damageUI);


	// HP減算
	TakeDamage(finalDamage);

	// スタン蓄積
	if (!isStun)
	{
		AddStunGauge(finalStunPower);
	}

	// ノックバック
	SetExternalVelocity(
		VScale(info.hitDir, info.knockBackPower)
	);

	SetLookDir(VScale(info.hitDir, -1));

	// 死亡判定
	if (IsDead())
	{
		ChangeState(std::make_shared<EnemyDeadState>());
		return;
	}

	// 被弾
	if (!isAttack)
	{
		auto state = std::make_shared<EnemyDamageState>();
		ChangeState(state);
		return;
	}
}

void Enemy::OnStun()
{
	EffectContainer::GetInstance().PlayEffect(
		"StunImpact",
		GetCapsuleCenter(),
		false
	);

	auto state =
		std::make_shared<EnemyStunState>();

	ChangeState(state);
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

void Enemy::UpdateAttackCoolDown()
{
	if (attackCooldown > 0.0f)
	{
		attackCooldown -=
			Time::GetInstance().GetDeltaTime() * 60.0f;

		if (attackCooldown < 0.0f)
		{
			attackCooldown = 0.0f;
		}
	}
}
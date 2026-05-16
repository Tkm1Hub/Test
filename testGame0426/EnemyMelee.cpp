#include "stdafx.h"
#include "EnemyMelee.h"
#include "EnemyChaseState.h"
#include "EnemyAttackState.h"
#include "AttackHitSphere.h"
#include "Objects.h"
#include "Player.h"
#include "HPBarUI.h"
#include "UIContainer.h"
#include "UIFactory.h"

void EnemyMelee::Init()
{
	Enemy::Init();
	pos = VGet(0.0f, 0.0f, 20.0f);
	MaxHP = param.HP;
	HP = MaxHP;
	maxMoveSpeed = param.maxMoveSpeed;
	bodyRadius = param.bodyRadius;
	bodyHeight = param.bodyHeight;

	// UI生成
	auto ui = UIFactory::CreateHPBarUI(
		std::static_pointer_cast<DamageableObject>(shared_from_this())
	);

	UIContainer::GetInstance().Add(ui);


	// attackData初期化
	attackData.combo =
	{
		// 1段目
		{
			param.windupTime, param.activeTime, param.recoveryTime,
			param.damage, param.attackMoveSpeed,param.attackHitRadius
		}
	};

	// ステート初期化
	auto state = std::make_shared<EnemyChaseState>();
	ChangeState(state);
}

void EnemyMelee::Update()
{
	Enemy::Update();
}

void EnemyMelee::Draw()
{
	DrawCapsule3D(
		GetCapsuleBottom(),
		GetCapsuleTop(),
		param.bodyRadius,
		8,
		GetColor(255, 0, 0),
		GetColor(0, 0, 0),
		TRUE
	);

	Object::Draw();
}

void EnemyMelee::Chase()
{
	Enemy::Chase();

	// Playerが攻撃範囲内に入るとAttackState
	if (GetDistanceToPlayer() <= param.attackRange)
	{
		auto state = std::make_shared<EnemyAttackState>();
		ChangeState(state);
		return;
	}
}

void EnemyMelee::Attack(const AttackStep& step)
{
	auto playerPtr = player.lock();
	if (!playerPtr) return;

	// プレイヤーの方向へ加速
	VECTOR attackDir = GetDirectionToPlayer();
	SetExternalVelocity(VScale(attackDir, step.attackMoveSpeed));

	// 前方にHitSphereを生成
	auto hitSphere = std::make_shared<AttackHitSphere>();

	// HitSphere初期化
	hitSphere->InitMelee(
		param.attackForwardOffset,
		step.attackHitRadius,
		step.damage,
		this,
		attackDir
	);

	Objects::GetInstance().Add(hitSphere);
}
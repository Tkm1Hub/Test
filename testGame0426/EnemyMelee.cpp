#include "stdafx.h"
#include "EnemyMelee.h"
#include "EnemyChaseState.h"
#include "AttackHitSphere.h"
#include "Objects.h"
#include "Player.h"
#include "HPBarUI.h"
#include "UIManager.h"

void EnemyMelee::Init()
{
	pos = VGet(0.0f, 0.0f, 10.0f);
	MaxHP = param.HP;
	HP = MaxHP;
	maxMoveSpeed = param.maxMoveSpeed;
	bodyRadius = param.bodyRadius;
	bodyHeight = param.bodyHeight;

	// attackData初期化
	attackData.combo =
	{
		// 1段目
		{
			param.windupTime, param.activeTime, param.recoveryTime,
			param.damage, param.attackMoveSpeed,param.attackHitRadius
		}
	};

	// HPBar生成
	auto HPBar = std::make_shared<HPBarUI>();
	HPBar->SetTarget(std::dynamic_pointer_cast<DamageableObject>(shared_from_this()));

	// UIリスト追加
	UIManager::GetInstance().Add(HPBar);

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
	hitSphere->Init(
		param.attackForwardOffset,
		step.attackHitRadius,
		step.damage,
		this
	);

	Objects::GetInstance().Add(hitSphere);
}
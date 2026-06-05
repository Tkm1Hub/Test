#include "stdafx.h"
#include "EnemyShooter.h"
#include "AttackHitSphere.h"
#include "EnemyAttackState.h"
#include "EnemyChaseState.h"
#include "Objects.h"
#include "Player.h"
#include "HPBarUI.h"
#include "UIContainer.h"
#include "UIFactory.h"

void EnemyShooter::Init()
{
	Enemy::Init();
	pos = VGet(20.0f, 30.0f, 0.0f);
	MaxHP = param.HP;
	HP = MaxHP;
	maxMoveSpeed = param.chaseSpeed;
	bodyRadius = param.bodyRadius;
	bodyHeight = param.bodyHeight;
    stunTime = param.stunTime;

	// UI生成
	auto ui = UIFactory::CreateHPBarUI(
		std::static_pointer_cast<CharacterBase>(shared_from_this())
	);

	UIContainer::GetInstance().Add(ui);

    // コンボ設定
    SetupCombo(param.combo);

    // ステート初期化
    auto state = std::make_shared<EnemyChaseState>();
    ChangeState(state);
}

void EnemyShooter::Update()
{
	Enemy::Update();
}

void EnemyShooter::Draw()
{
	DrawCapsule3D(
		GetCapsuleBottom(),
		GetCapsuleTop(),
		param.bodyRadius,
		8,
		GetColor(0, 255, 0),
		GetColor(0, 0, 0),
		TRUE
	);

	Object::Draw();
}

void EnemyShooter::Chase()
{
    auto playerPtr = player.lock();

    if (!playerPtr)
        return;

    // プレイヤー方向
    VECTOR dir =
        GetDirectionToPlayer();

    // 距離
    float distance =
        GetDistanceToPlayer();

    // 近すぎる → 離れる
    if (distance < param.keepDistance - param.toleranceDistance)
    {
        MoveTo(
            VSub(
                pos,
                VScale(dir, 100.0f)
            )
        );
    }
    // 遠すぎる → 近づく
    else if (distance > param.keepDistance + param.toleranceDistance)
    {
        MoveTo(playerPtr->GetPosition());
    }
    // 適正距離 → 停止
    else
    {
        SetMoveVelocity(
            VGet(0, 0, 0)
        );

        auto state = std::make_shared<EnemyAttackState>();
        ChangeState(state);
        return;

    }
}

void EnemyShooter::Attack(const AttackStep& step)
{

    auto playerPtr = player.lock();
    if (!playerPtr) return;

    VECTOR attackDir =
        GetDirectionToPlayer();

    SetLookDir(attackDir);

    auto bullet =
        std::make_shared<AttackHitSphere>();

    bullet->InitProjectile(
        VAdd(
            GetCapsuleCenter(),
            VScale(
                attackDir,
                step.attackForwardOffset
            )
        ),
        step.attackHitRadius,
        step.damage,
        step.stunPower,
        step.knockBackPower,
        this,
        attackDir,
        param.bulletSpeed
    );
    Objects::GetInstance().Add(bullet);
}
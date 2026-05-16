#include "stdafx.h"
#include "Objects.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "AttackHitSphere.h"
#include "Time.h"
#include "PlayerDamageState.h"
#include "Enemy.h"

void Player::SetCamera(const std::weak_ptr<Camera>& cameraPtr)
{
	camera = cameraPtr;
}

void Player::ChangeState(std::shared_ptr<PlayerStateBase> a_spState)
{
	a_spState->SetOwner(this);
	stateMachine.ChangeState(a_spState);
}

void Player::Init()
{
	// 初期ステートをIdleに設定
	auto spIdleState = std::make_shared<PlayerIdleState>();
	ChangeState(spIdleState);

	MaxHP = param.HP;
	HP = MaxHP;
	maxMoveSpeed = param.maxMoveSpeed;
	bodyRadius = param.bodyRadius;
	bodyHeight = param.bodyHeight;
	team = Team::Player;

	// attackData初期化
	attackData.combo =
	{
		// 1段目
		{
			param.windupTime, param.activeTime, param.recoveryTime,
			param.attackPower, param.attackMoveSpeed,param.attackHitRadius
		}
	};
}

void Player::Update()
{
	moveDir = VGet(0.0f, 0.0f, 0.0f);		// 毎フレーム移動入力をリセット

	// ステート更新
	stateMachine.Update();

	// 方向更新
	RotateAngle();

	// 重力を適用
	ApplyGravity();

	// 速度を適用
	ApplyVelocity();
}

void Player::Draw()
{
	DrawCapsule3D(
		GetCapsuleBottom(),
		GetCapsuleTop(),
		param.bodyRadius,
		8,
		GetColor(18, 105, 204),
		GetColor(0, 0, 0),
		TRUE
	);

	printfDx("[Player.moveVelocity : %f, %f, %f ]", moveVelocity.x, moveVelocity.y, moveVelocity.z);

	Object::Draw();
}


void Player::MoveInput()
{
	if (auto cam = camera.lock())
	{
		// スティック入力
		float stickX = Input::GetInput().GetLeftStickX();
		float stickY = Input::GetInput().GetLeftStickY();

		if (fabs(stickX) > 0.01f || fabs(stickY) > 0.01f)
		{
			VECTOR camForward = cam->GetFoward();
			camForward.y = 0.0f;
			camForward = VNorm(camForward);

			VECTOR camRight = VCross(VGet(0, 1, 0), camForward);

			camRight = VNorm(camRight);

			moveDir = VAdd(
					VScale(camRight, stickX),
					VScale(camForward, stickY)
				);

			moveDir = VNorm(moveDir);
			lookDir = moveDir;
		}
	}
}

void Player::Attack(const AttackStep& step)
{
	VECTOR attackDir = VGet(0, 0, 0);

	// ターゲット検索
	SearchTarget();

	auto targetPtr = target.lock();

	// ターゲットがいる
	if (targetPtr)
	{
		attackDir =
			VSub(
				targetPtr->GetPosition(),
				pos
			);

		attackDir.y = 0.0f;

		attackDir = VNorm(attackDir);
	}
	// 入力方向
	else if (VSize(moveDir) > 0.1f)
	{
		attackDir = moveDir;
	}
	// 前方向
	else
	{
		attackDir = forward;
	}

	// 向き更新
	SetLookDir(attackDir);
	// 前方へ加速
	SetExternalVelocity(
		VScale(
			attackDir,
			step.attackMoveSpeed
		));

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

void Player::OnHit(const DamageInfo& info)
{
	DamageableObject::OnHit(info);

	auto state = std::make_shared<PlayerDamageState>();
	ChangeState(state);
	return;
}

void Player::SearchTarget()
{
	float nearestDistance = FLT_MAX;

	std::shared_ptr<Enemy> nearestEnemy = nullptr;

	if (auto cam = camera.lock())
	{
		for (auto& obj : Objects::GetInstance().objects)
		{
			auto enemy =
				std::dynamic_pointer_cast<Enemy>(obj);

			if (!enemy)
				continue;

			if (!enemy->GetIsActive())
				continue;

			// 死亡除外
			if (enemy->IsDead())
				continue;

			// カメラから敵の方向
			VECTOR toEnemy =
				VSub(
					enemy->GetPosition(),
					cam->GetPosition()
				);

			float distance = VSize(toEnemy);

			// 正規化
			VECTOR dir = VNorm(toEnemy);

			// 前方向判定
			float dot = VDot(cam->GetFoward(), dir);

			// 前方のみ
			if (dot < 0.5f)
				continue;

			// 一番近い敵
			if (distance < nearestDistance)
			{
				nearestDistance = distance;
				nearestEnemy = enemy;
			}
		}
	}

	target = nearestEnemy;
}
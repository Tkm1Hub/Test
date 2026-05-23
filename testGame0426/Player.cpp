#include "stdafx.h"
#include "Objects.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "AttackHitSphere.h"
#include "Time.h"
#include "PlayerDamageState.h"
#include "PlayerJustDodgeState.h"
#include "PlayerDodgeState.h"
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

	// コンボ設定
	SetupCombo(param.combo);
}

void Player::Update()
{
	moveDir = VGet(0.0f, 0.0f, 0.0f);		// 毎フレーム移動入力をリセット

	// ステート更新
	stateMachine.Update();

	// ターゲット検索
	SearchTarget();

	// ロックオン切り替え
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_LEFT_THUMB))
	{
		ToggleLockOn();
	}

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

VECTOR Player::GetInputDir() const
{
	VECTOR inputDir = VGet(0.0f, 0.0f, 0.0f);

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

			inputDir = VAdd(
				VScale(camRight, stickX),
				VScale(camForward, stickY)
			);

			inputDir = VNorm(inputDir);

		}
	}
	return inputDir;
}

void Player::MoveInput()
{
	moveDir = GetInputDir();
	lookDir = moveDir;
}

void Player::Attack(const AttackStep& step)
{
	VECTOR attackDir = VGet(0, 0, 0);

	// 攻撃速度設定
	float atkSpeed = GetAttackMoveSpeed(step);

	auto targetPtr = target.lock();

	float distance = 0.0f;

	// ターゲットがいる
	if (targetPtr)
	{
		attackDir =
			VSub(
				targetPtr->GetPosition(),
				pos
			);

		attackDir.y = 0.0f;

		distance = VSize(attackDir);

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
			atkSpeed
		));

	// 前方にHitSphereを生成
	auto hitSphere = std::make_shared<AttackHitSphere>();

	// HitSphere初期化
	hitSphere->InitMelee(
		step.damage,
		step.stunPower,
		step.attackHitRadius,
		step.attackForwardOffset,
		step.knockBackPower,
		this,
		attackDir
	);

	Objects::GetInstance().Add(hitSphere);
}

VECTOR Player::GetAttackDirection()
{

	auto targetPtr = target.lock();

	VECTOR attackDir = VGet(0, 0, 0);

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
	else if (VSize(moveDir) > 0.1f)
	{
		attackDir = moveDir;
	}
	else
	{
		attackDir = forward;
	}

	return attackDir;
}

float Player::GetAttackMoveSpeed(const AttackStep& step)
{

	auto targetPtr = target.lock();

	// ターゲットいないなら通常速度
	if (!targetPtr)
	{
		return step.attackMoveSpeed;
	}

	VECTOR toEnemy =
		VSub(
			targetPtr->GetPosition(),
			pos
		);

	toEnemy.y = 0.0f;

	float distance = VSize(toEnemy);

	//--------------------------------
	// 加速開始距離
	//--------------------------------

	float assistDistance = 30.0f;

	//--------------------------------
	// 基本速度
	//--------------------------------

	float moveSpeed =
		step.attackMoveSpeed;

	//--------------------------------
	// 遠い分だけ加速
	//--------------------------------

	if (distance > assistDistance)
	{
		float extraDistance =
			distance - assistDistance;

		moveSpeed +=
			extraDistance * 0.15f;
	}

	//--------------------------------
	// 上限
	//--------------------------------

	float maxSpeed =
		step.attackMoveSpeed * 3.0f;

	if (moveSpeed > maxSpeed)
	{
		moveSpeed = maxSpeed;
	}

	return moveSpeed;
}
// 敵の攻撃接触
void Player::OnHit(const DamageInfo& info)
{
	DamageableObject::OnHit(info);

	auto currentState = stateMachine.GetCurrentState();

	// 回避中だと
	if (currentState->GetName() == "Dodge")
	{
		auto state = std::make_shared<PlayerJustDodgeState>();
		ChangeState(state);
		return;
	}
	else if (currentState->GetName() == "JustDodge")
	{
		return;
	}

	auto state = std::make_shared<PlayerDamageState>();
	ChangeState(state);
	return;
}

void Player::SearchTarget()
{
	//--------------------------------
	// 現在target維持
	//--------------------------------

	auto currentTarget = target.lock();

	if (!Input::GetInput().GetIsMoveLStick())
	{
		if (currentTarget &&
			!currentTarget->IsDead())
		{
			return;
		}
	}

	//--------------------------------
	// 新規検索
	//--------------------------------

	float nearestDistance = FLT_MAX;

	std::shared_ptr<Enemy> nearestEnemy = nullptr;

	if (auto cam = camera.lock())
	{
		VECTOR inputDir = GetInputDir();

		VECTOR camForward =
			cam->GetFoward();

		camForward.y = 0.0f;
		camForward = VNorm(camForward);

		for (auto& obj : Objects::GetInstance().objects)
		{
			auto enemy =
				std::dynamic_pointer_cast<Enemy>(obj);

			if (!enemy)
				continue;

			if (!enemy->GetIsActive())
				continue;

			if (enemy->IsDead())
				continue;

			//--------------------------------
			// プレイヤー→敵
			//--------------------------------

			VECTOR toEnemy =
				VSub(
					enemy->GetPosition(),
					pos
				);

			toEnemy.y = 0.0f;

			float distance =
				VSize(toEnemy);

			if (distance > param.attackSupportDistance)
				continue;

			VECTOR enemyDir =
				VNorm(toEnemy);

			//--------------------------------
			// カメラ前方
			//--------------------------------

			VECTOR cameraToEnemy =
				VSub(
					enemy->GetPosition(),
					cam->GetPosition()
				);

			cameraToEnemy.y = 0.0f;

			VECTOR camEnemyDir =
				VNorm(cameraToEnemy);

			float camDot =
				VDot(
					camForward,
					camEnemyDir
				);

			if (camDot < 0.3f)
				continue;

			//--------------------------------
			// 入力方向
			//--------------------------------

			if (VSize(inputDir) > 0.1f)
			{
				float inputDot =
					VDot(
						inputDir,
						enemyDir
					);

				if (inputDot < 0.5f)
					continue;
			}

			//--------------------------------
			// 一番近い敵
			//--------------------------------

			if (distance < nearestDistance)
			{
				nearestDistance = distance;
				nearestEnemy = enemy;
			}
		}
	}

	if (nearestEnemy)
	{
		target = nearestEnemy;
	}
}

void Player::ToggleLockOn()
{
	if (isLockOn)
	{
		isLockOn = false;
		lockOnTarget.reset();
		return;
	}

	SearchTarget();

	if (auto targetPtr = target.lock())
	{
		lockOnTarget = targetPtr;
		isLockOn = true;
	}
}
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
	currentBulletNum = 0;
	maxMoveSpeed = param.maxMoveSpeed;
	bodyRadius = param.bodyRadius;
	bodyHeight = param.bodyHeight;
	team = Team::Player;

	// コンボ設定
	SetupCombo(param.combo);
	fireData = param.bullet;
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

	//---------------------------------
	// Aim中はtarget方向を見る
	//---------------------------------

	if (isAim)
	{
		auto targetPtr = target.lock();

		if (targetPtr)
		{
			lookDir =
				VSub(
					targetPtr->GetCapsuleCenter(),
					pos
				);

			lookDir.y = 0;

			lookDir = VNorm(lookDir);
		}
	}
	else
	{
		//---------------------------------
		// 通常時は入力方向を見る
		//---------------------------------

		lookDir = moveDir;
	}
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

void Player::Fire(const AttackStep& step)
{
	auto targetPtr = target.lock();

	VECTOR fireDir = VSub(targetPtr->GetPosition(), pos);
	fireDir = VNorm(fireDir);

	// ノックバック
	VECTOR KnockBackDir = VScale(forward, -1);

	SetExternalVelocity(
		VScale(
			KnockBackDir,
			param.fireKnockBackPower
		));

	// 前方にHitSphereを生成
	auto bullet = std::make_shared<AttackHitSphere>();

	// HitSphere初期化
	bullet->InitProjectile(
		GetCapsuleCenter(),
		step.attackHitRadius,
		step.damage,
		step.stunPower,
		step.knockBackPower,
		this,
		fireDir,
		param.bulletSpeed
	);
	Objects::GetInstance().Add(bullet);
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
	auto currentTarget = target.lock();

	//--------------------------------
	// ターゲット死亡
	//--------------------------------

	if (currentTarget &&
		currentTarget->IsDead())
	{
		target.reset();
		isLockOn = false;
		currentTarget = nullptr;
	}

	//--------------------------------
	// LockOnまたはAim中
	//--------------------------------

	if (isLockOn || isAim)
	{
		//--------------------------------
		// ターゲット無し
		//--------------------------------

		if (!currentTarget)
		{
			isLockOn = false;
			return;
		}

		float stickX =
			Input::GetInput().GetRightStickX();

		//--------------------------------
		// スティック戻したら再切替可能
		//--------------------------------

		if (fabs(stickX) < 0.3f)
		{
			canSwitchTarget = true;
			return;
		}

		//--------------------------------
		// 既に切替済み
		//--------------------------------

		if (!canSwitchTarget)
		{
			return;
		}

		//--------------------------------
		// 倒し切ってない
		//--------------------------------

		if (fabs(stickX) < 0.8f)
		{
			return;
		}

		canSwitchTarget = false;

		//--------------------------------
		// 現在ターゲット方向
		//--------------------------------

		VECTOR currentDir =
			VSub(
				currentTarget->GetPosition(),
				pos
			);

		currentDir.y = 0.0f;

		currentDir =
			VNorm(currentDir);

		std::shared_ptr<Enemy> nextTarget = nullptr;

		float bestDot = -1.0f;

		//--------------------------------
		// 敵探索
		//--------------------------------

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

			if (enemy == currentTarget)
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

			if (distance >
				param.SearchEnemyDistance)
			{
				continue;
			}

			VECTOR enemyDir =
				VNorm(toEnemy);

			//--------------------------------
			// 左右判定
			//--------------------------------

			VECTOR cross =
				VCross(
					currentDir,
					enemyDir
				);

			//--------------------------------
			// 右切替
			//--------------------------------

			if (stickX > 0.0f)
			{
				if (cross.y <= 0.0f)
					continue;
			}
			//--------------------------------
			// 左切替
			//--------------------------------
			else
			{
				if (cross.y >= 0.0f)
					continue;
			}

			//--------------------------------
			// 正面寄り優先
			//--------------------------------

			float dot =
				VDot(
					currentDir,
					enemyDir
				);

			if (dot > bestDot)
			{
				bestDot = dot;
				nextTarget = enemy;
			}
		}

		//--------------------------------
		// ターゲット更新
		//--------------------------------

		if (nextTarget)
		{
			target = nextTarget;
		}

		return;
	}

	//--------------------------------
	// 通常ターゲット維持
	//--------------------------------

	if (!Input::GetInput().GetIsMoveLStick())
	{
		if (currentTarget)
		{
			return;
		}
	}

	//--------------------------------
	// 通常ターゲット検索
	//--------------------------------

	float nearestDistance = FLT_MAX;

	std::shared_ptr<Enemy> nearestEnemy = nullptr;

	if (auto cam = camera.lock())
	{
		VECTOR inputDir = GetInputDir();

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

			VECTOR toEnemy =
				VSub(
					enemy->GetPosition(),
					pos
				);

			toEnemy.y = 0.0f;

			float distance =
				VSize(toEnemy);

			if (distance >
				param.SearchEnemyDistance)
			{
				continue;
			}

			VECTOR enemyDir =
				VNorm(toEnemy);

			float dot =
				VDot(
					inputDir,
					enemyDir
				);

			if (dot < 0.5f)
				continue;

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
		return;
	}

	auto targetPtr = target.lock();

	if (targetPtr &&
		!targetPtr->IsDead())
	{
		isLockOn = true;
	}
}
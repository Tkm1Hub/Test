#include "stdafx.h"
#include "Objects.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "AttackHitSphere.h"
#include "Time.h"
#include "PlayerDamageState.h"

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
	// 前方へ加速
	VECTOR attackDir = moveDir;

	// 入力が無ければ前方向を使用
	if (VSize(attackDir) <= 0.1f)
	{
		attackDir = forward;
	}

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

void Player::OnHit(const DamageInfo& info)
{
	DamageableObject::OnHit(info);

	auto state = std::make_shared<PlayerDamageState>();
	ChangeState(state);
	return;
}
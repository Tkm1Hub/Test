#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "Time.h"

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
}

void Player::Update()
{
	input = VGet(0.0f, 0.0f, 0.0f);		// 毎フレーム移動入力をリセット

	// ステート更新
	stateMachine.Update();

	// 方向更新
	RotateCharacter();

	// 重力を適用
	ApplyGravity();

	// 速度を適用
	ApplyVelocity();
}

void Player::Draw()
{
	DrawCapsule3D(pos, VAdd(pos, VGet(0.0f, 5.0f, 0.0f)), 2.0f, 8, GetColor(18, 105, 204), GetColor(0, 0, 0),TRUE);

	// 向いてる方向表示
	DrawLine3D(
		VAdd(pos, VGet(0.0f, 2.5f, 0.0f)),
		VAdd(
			VAdd(pos, VGet(0.0f, 2.5f, 0.0f)),
			VScale(forward, 10.0f)
		),
		GetColor(255, 0, 0)
	);

	// 入力方向表示
	DrawLine3D(
		VAdd(pos, VGet(0.0f, 2.0f, 0.0f)),
		VAdd(
			VAdd(pos, VGet(0.0f, 2.0f, 0.0f)),
			VScale(input, 8.0f)
		),
		GetColor(0, 255, 0)
	);

	// Velocity
	DrawLine3D(
		pos,
		VAdd(pos, VScale(moveVelocity, 6.5f)),
		GetColor(0, 0, 255)
	);


	printfDx("[Player.moveVelocity : %f, %f, %f ]", moveVelocity.x, moveVelocity.y, moveVelocity.z);
}

void Player::ApplyVelocity()
{
	// HACK: 移動距離が0.01未満で微妙に移動していた場合はじんわり移動してバグる
	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (VSize(input) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	// 移動速度を計算
	culcMoveSpeed();

	float dt =
		Time::GetInstance().GetScaledDeltaTime()
		* 60.0f;

	moveVelocity.y = verticalVelocity;	// 垂直移動速度を加算

	VECTOR filalVelocity = VAdd(moveVelocity, externalVelocity);

	pos = VAdd(pos,VScale(filalVelocity,dt));

	if (pos.y < 0.0f)
	{
		isGround = true;
		pos.y = 0.0f;
		verticalVelocity = 0.0f;
	}

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
			// カメラ基準の移動ベクトルを計算
			VECTOR camForward = cam->GetFoward();
			VECTOR camRight = VCross(camForward, VGet(0.0f, 1.0f, 0.0f));
			camRight = VNorm(camRight);
			input = VAdd(VScale(camRight, stickX), VScale(camForward, stickY));
			input = VNorm(input);
		}
	}
}


void Player::culcMoveSpeed()
{
	float dt =
		Time::GetInstance().GetScaledDeltaTime()
		* 60.0f;

	// 移動中
	if (isMove)
	{
		moveVelocity.x += forward.x * Accel * dt;
		moveVelocity.z += forward.z * Accel * dt;
	}
	else
	{
		float decel = powf(Decel, dt);

		moveVelocity.x *= decel * dt;
		moveVelocity.z *= decel * dt;

		// 微小値停止
		if (fabs(moveVelocity.x) < 0.001f)
			moveVelocity.x = 0.0f;

		if (fabs(moveVelocity.z) < 0.001f)
			moveVelocity.z = 0.0f;
	}

	// 外的速度の減衰
	float extDecel = powf(Decel, dt);

	externalVelocity.x *= extDecel;
	externalVelocity.z *= extDecel;

	// 最大速度制限
	float speed =
		sqrtf(moveVelocity.x * moveVelocity.x +
			moveVelocity.z * moveVelocity.z);

	if (speed > MaxMoveSpeed)
	{
		float rate = MaxMoveSpeed / speed;

		moveVelocity.x *= rate;
		moveVelocity.z *= rate;
	}
}

void Player::RotateCharacter()
{
	// 入力がないなら回転しない
	if (VSize(input) <= 0.01f) return;

	float dt =
		Time::GetInstance().GetScaledDeltaTime()
		* 60.0f;

	// 現在方向 → 入力方向へ補間
	forward = VNorm(
		VAdd(
			VScale(forward, 1.0f - param.angleSpeed),
			VScale(input, param.angleSpeed)
		)
	);
}
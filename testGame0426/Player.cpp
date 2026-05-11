#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "PlayerIdleState.h"

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

	// 重力を適用
	ApplyGravity();

	// 速度を適用
	ApplyVelocity();
}

void Player::Draw()
{
	DrawCapsule3D(pos, VAdd(pos, VGet(0.0f, 5.0f, 0.0f)), 2.0f, 8, GetColor(18, 105, 204), GetColor(0, 0, 0),TRUE);
	printfDx("[Player.moveVelocity : %f, %f, %f ]", moveVelocity.x, moveVelocity.y, moveVelocity.z);
	printfDx("");
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

	moveVelocity.y = verticalVelocity;	// 垂直移動速度を加算

	pos = VAdd(pos, moveVelocity);

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
	// 移動中
	if (isMove)
	{
		moveVelocity.x += input.x * Accel;
		moveVelocity.z += input.z * Accel;
	}
	else
	{
		moveVelocity.x *= Decel;
		moveVelocity.z *= Decel;

		// 微小値停止
		if (fabs(moveVelocity.x) < 0.001f)
			moveVelocity.x = 0.0f;

		if (fabs(moveVelocity.z) < 0.001f)
			moveVelocity.z = 0.0f;
	}

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
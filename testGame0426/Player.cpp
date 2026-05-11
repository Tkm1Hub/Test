#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"

void Player::SetCamera(const std::weak_ptr<Camera>& cameraPtr)
{
	camera = cameraPtr;
}

void Player::Init()
{

}

void Player::Update()
{

	PlayerMove();
}

void Player::Draw()
{
	DrawCapsule3D(pos, VAdd(pos, VGet(0.0f, 5.0f, 0.0f)), 2.0f, 8, GetColor(18, 105, 204), GetColor(0, 0, 0),TRUE);
	printfDx("[Player.moveVec : %f, %f, %f ]", moveVec.x, moveVec.y, moveVec.z);
}

void Player::PlayerMove()
{
	VECTOR input = GetMoveInput();

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
	culcMoveSpeed(input);

	moveVelocity.y = verticalVelocity;	// 垂直移動速度を加算

	pos = VAdd(pos, moveVelocity);
}

VECTOR Player::GetMoveInput()
{
	if (auto cam = camera.lock())
	{

		VECTOR mVec = VGet(0.0f, 0.0f, 0.0f);

		// スティック入力
		float stickX = Input::GetInput().GetLeftStickX();
		float stickY = Input::GetInput().GetLeftStickY();

		if (fabs(stickX) > 0.01f || fabs(stickY) > 0.01f)
		{
			// カメラ基準の移動ベクトルを計算
			VECTOR camForward = cam->GetFoward();
			VECTOR camRight = VCross(camForward, VGet(0.0f, 1.0f, 0.0f));
			camRight = VNorm(camRight);
			mVec = VAdd(VScale(camRight, stickX), VScale(camForward, stickY));
			mVec = VNorm(mVec);
		}
		return mVec;
	}
}

void Player::culcMoveSpeed(const VECTOR& input)
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
#include "Camera.h"
#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Time.h"

void Camera::SetPlayer(const std::weak_ptr<Player>& playerPtr)
{
	player = playerPtr;
}

void Camera::Init()
{
	angleV = 0.0f; // 上下角度リセット
	angleH = 0.0f; // 水平角度リセット

	if (auto p = player.lock())
	{
		VECTOR playerPos = p->GetPosition();
		VECTOR forward = p->GetForward(); // プレイヤーの前方向

		// 注視点はプレイヤーの頭上
		target = VAdd(playerPos, VGet(0.0f, LOOK_OFFSET_Y, 0.0f));

		// カメラはプレイヤーの後ろにDISTANCE_OFFSETだけ離す
		pos = VSub(target, VScale(forward, DISTANCE_OFFSET));
	}

	// カメラ設定
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 5.0f, -10.0f), VGet(0.0f, 5.0f, 1.0f));
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
}

void Camera::Update()
{
	if (auto p = player.lock())
	{
		VECTOR playerPos = p->GetPosition();

		// カメラの旋回速度を計算
		//currentAngleSpeed = CalcAngleSpeed();

		// 入力
		InputAngle();

		//カメラの注視点はプレイヤー座標から規定値分高い座標
		target = VAdd(playerPos, VGet(0.0f, LOOK_OFFSET_Y, 0.0f));

		// カメラの方向を保存
		forward = VSub(target, pos);
		forward.y = 0.0f;
		forward = VNorm(forward);

		// カメラの座標を補正する
		FixCameraPosition();

		// 位置と注視点の設定
		SetCameraPositionAndTarget_UpVecY(pos, target);
	}
}

float Camera::CalcAngleSpeed()
{
	float stickAngle = Input::GetInput().GetRightStickPower();
	float stickPower = abs(stickAngle) / 1000.0f;

	// 傾きに応じた最大速度を計算
	float maxSpeed = MAX_ANGLE_SPEED * stickPower;

	// 加速 or 減速
	if (Input::GetInput().GetIsMoveRStick())
	{
		currentAngleSpeed += ACCEL; // 加速量
		currentAngleSpeed = min(currentAngleSpeed, maxSpeed); // maxSpeedで制限
	}
	else
	{
		currentAngleSpeed -= DECEL; // 減速は固定
		currentAngleSpeed = max(currentAngleSpeed, 0.0f); // マイナスにならないように
	}

	// フラグ
	isMove = (currentAngleSpeed > 0.0f);

	return currentAngleSpeed;

}

void Camera::InputAngle()
{
	float dt =
		Time::GetInstance().GetScaledDeltaTime()
		* 60.0f;

	float stickX = Input::GetInput().GetRightStickX();
	float stickY = Input::GetInput().GetRightStickY();

	// 感度
	float sensitivity = 0.03f;

	// 横回転
	angleH += stickX * sensitivity * dt;

	// 縦回転
	angleV += stickY * sensitivity * dt;

	// 縦角度制限
	float limit = DX_PI_F / 2.0f - 0.2f;

	if (angleV > limit)
		angleV = limit;

	if (angleV < -limit)
		angleV = -limit;
}

void Camera::FixCameraPosition()
{
	// 水平方向の回転はＹ軸回転
	auto rotY = MGetRotY(angleH);

	// 垂直方向の回転はＺ軸回転 )
	auto rotZ = MGetRotZ(angleV);

	// カメラからプレイヤーまでの初期距離をセット
	float cameraPlayerLength = DISTANCE_OFFSET;

	// カメラの座標を算出
	// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
	// 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
	// 注視点の座標を足したものがカメラの座標
	pos = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), target);
}
#include "stdafx.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "Time.h"

void Camera::SetPlayer(
	const std::weak_ptr<Player>& playerPtr
)
{
	player = playerPtr;
}

void Camera::Init()
{
	angleV = 0.0f;
	angleH = 0.0f;

	SetCameraNearFar(
		CAMERA_NEAR,
		CAMERA_FAR
	);
}

void Camera::Update()
{
	auto p = player.lock();

	if (!p)
		return;

	//--------------------------------
	// ロックオン切り替え検知
	//--------------------------------

	bool isLockOn =
		p->GetIsLockOn();

	if (isLockOn != prevLockOn)
	{
		isTransition = true;

		transitionTimer = 0.0f;

		transitionStartPos = pos;
		transitionStartTarget = target;

		prevLockOn = isLockOn;
	}

	//--------------------------------
	// カメラ更新
	//--------------------------------

	if (p->GetStateName() == "Aim")
	{
		UpdateAimCamera();
	}
	else if (isLockOn)
	{
		UpdateLockOnCamera();
	}
	else
	{
		UpdateNormalCamera();
	}

	//--------------------------------
	// 補間更新
	//--------------------------------

	if (isTransition)
	{
		UpdateTransition();
	}

	//--------------------------------
	// forward更新
	//--------------------------------

	forward =
		VSub(target, pos);

	forward.y = 0.0f;

	forward = VNorm(forward);

	//--------------------------------
	// カメラ反映
	//--------------------------------

	SetCameraPositionAndTarget_UpVecY(
		pos,
		target
	);
}

void Camera::UpdateNormalCamera()
{
	auto p = player.lock();

	if (!p)
		return;

	//--------------------------------
	// 回転入力
	//--------------------------------

	InputAngle();

	VECTOR playerPos =
		p->GetPosition();

	//--------------------------------
	// 注視点
	//--------------------------------

	target =
		VAdd(
			playerPos,
			VGet(
				0,
				LOOK_OFFSET_Y,
				0
			)
		);

	//--------------------------------
	// カメラ位置
	//--------------------------------

	FixCameraPosition();

	//--------------------------------
	// 遷移先保存
	//--------------------------------

	transitionGoalPos = pos;
	transitionGoalTarget = target;
}

void Camera::UpdateLockOnCamera()
{
	auto p = player.lock();

	if (!p)
		return;

	auto enemy =
		p->GetLockOnTarget().lock();

	//--------------------------------
	// ターゲット消失
	//--------------------------------

	if (!enemy ||
		enemy->IsDead())
	{
		p->SetIsLockOn(false);
		return;
	}

	//--------------------------------
	// 座標取得
	//--------------------------------

	VECTOR playerPos =
		p->GetPosition();

	VECTOR enemyPos =
		enemy->GetPosition();

	playerPos.y += LOOK_OFFSET_Y;
	enemyPos.y += 20.0f;

	//--------------------------------
	// 中間点
	//--------------------------------

	VECTOR center =
		VScale(
			VAdd(playerPos, enemyPos),
			0.5f
		);

	target = center;

	//--------------------------------
	// プレイヤー→敵
	//--------------------------------

	VECTOR toEnemy =
		VSub(
			enemyPos,
			playerPos
		);

	float distance =
		VSize(toEnemy);

	toEnemy.y = 0.0f;

	VECTOR dir =
		VNorm(toEnemy);

	//--------------------------------
	// 横ベクトル
	//--------------------------------

	VECTOR right =
		VCross(
			VGet(0, 1, 0),
			dir
		);

	right = VNorm(right);

	//--------------------------------
	// 左右切り替え
	//--------------------------------

	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		sideSign *= -1;
	}

	//--------------------------------
	// 距離に応じて引く
	//--------------------------------

	float cameraDistance =
		LOCKON_BASE_DISTANCE +
		distance * 0.7f;

	cameraDistance =
		std::clamp(
			cameraDistance,
			LOCKON_BASE_DISTANCE,
			LOCKON_MAX_DISTANCE
		);

	//--------------------------------
	// 後方位置
	//--------------------------------

	VECTOR backPos =
		VSub(
			center,
			VScale(dir, cameraDistance)
		);

	//--------------------------------
	// 横にずらす
	//--------------------------------

	backPos =
		VAdd(
			backPos,
			VScale(
				right,
				SIDE_OFFSET * sideSign
			)
		);

	//--------------------------------
	// 高さ
	//--------------------------------

	backPos.y += LOCKON_HEIGHT;

	//--------------------------------
	// 補間
	//--------------------------------

	pos =
		VAdd(
			pos,
			VScale(
				VSub(backPos, pos),
				SMOOTH_SPEED
			)
		);

	target =
		VAdd(
			target,
			VScale(
				VSub(center, target),
				SMOOTH_SPEED
			)
		);

	//--------------------------------
	// ロックオン角度同期
	//--------------------------------

	VECTOR cameraForward =
		VSub(target, pos);

	cameraForward.y = 0.0f;

	cameraForward =
		VNorm(cameraForward);

	angleH =
		atan2f(
			cameraForward.x,
			cameraForward.z
		);

	//--------------------------------
	// 遷移先保存
	//--------------------------------

	transitionGoalPos = pos;
	transitionGoalTarget = target;
}

void Camera::UpdateAimCamera()
{
	auto p = player.lock();

	if (!p)
		return;

	auto enemy =
		p->GetTarget().lock();

	//--------------------------------
	// ターゲット消失
	//--------------------------------

	if (!enemy ||
		enemy->IsDead())
	{
		p->SetIsLockOn(false);
		return;
	}

	//--------------------------------
	// 座標
	//--------------------------------

	VECTOR playerPos =
		p->GetPosition();

	playerPos.y += LOOK_OFFSET_Y;

	VECTOR enemyPos =
		enemy->GetCapsuleCenter();

	//--------------------------------
	// プレイヤー→敵
	//--------------------------------

	VECTOR toEnemy =
		VSub(enemyPos, playerPos);

	toEnemy.y = 0.0f;

	VECTOR dir =
		VNorm(toEnemy);

	//--------------------------------
	// 横方向
	//--------------------------------

	VECTOR right =
		VCross(
			VGet(0, 1, 0),
			dir
		);

	right = VNorm(right);

	//--------------------------------
	// TPS肩越し位置
	//--------------------------------

	VECTOR backPos =
		VSub(
			playerPos,
			VScale(dir, AIM_BASE_DISTANCE)
		);

	// 肩越し
	backPos =
		VAdd(
			backPos,
			VScale(right, SIDE_AIM_OFFSET)
		);

	//--------------------------------
	// 高さ
	//--------------------------------

	backPos.y += AIM_HEIGHT;

	//--------------------------------
	// 補間
	//--------------------------------

	pos =
		VAdd(
			pos,
			VScale(
				VSub(backPos, pos),
				SMOOTH_SPEED
			)
		);

	//--------------------------------
	// target
	//--------------------------------

	target = enemyPos;

	//--------------------------------
	// カメラforward
	//--------------------------------

	forward =
		VNorm(
			VSub(target, pos)
		);

	//--------------------------------
	// カメラ角度
	//--------------------------------

	angleH =
		atan2f(
			forward.x,
			forward.z
		);

	//--------------------------------
	// 保存
	//--------------------------------

	transitionGoalPos = pos;
	transitionGoalTarget = target;
}

void Camera::InputAngle() {

	float dt = Time::GetInstance().GetScaledDeltaTime() * 60.0f;

	float stickX = Input::GetInput().GetRightStickX();
	float stickY = Input::GetInput().GetRightStickY();
	float sensitivity = 0.03f;

	//-------------------------------- 
	// 横回転 
	//--------------------------------

	angleH += stickX * sensitivity * dt;
	
	//-------------------------------- 
	// 縦回転 
	//--------------------------------
	
	angleV -= stickY * sensitivity * dt;
	
	//-------------------------------- 
	// 縦制限 
	//--------------------------------
	
	float limit = DX_PI_F / 2.0f - 0.2f;
	
	if (angleV > limit) { angleV = limit; }
	if (angleV < -limit) { angleV = -limit; }

}

void Camera::FixCameraPosition()
{
	MATRIX rotY =
		MGetRotY(angleH);

	MATRIX rotX =
		MGetRotX(angleV);

	VECTOR offset =
		VTransform(
			VTransform(
				VGet(
					0,
					0,
					-DISTANCE_OFFSET
				),
				rotX
			),
			rotY
		);

	pos =
		VAdd(
			target,
			offset
		);
}

void Camera::StartTransition(
	const VECTOR& goalPos,
	const VECTOR& goalTarget
)
{
	isTransition = true;

	transitionTimer = 0.0f;

	transitionStartPos = pos;
	transitionStartTarget = target;

	transitionGoalPos = goalPos;
	transitionGoalTarget = goalTarget;
}

void Camera::UpdateTransition()
{
	float dt =
		Time::GetInstance().GetScaledDeltaTime();

	transitionTimer += dt;

	float t =
		transitionTimer /
		TRANSITION_TIME;

	t = std::clamp(t, 0.0f, 1.0f);

	pos =
		LerpVec(
			transitionStartPos,
			transitionGoalPos,
			t
		);

	target =
		LerpVec(
			transitionStartTarget,
			transitionGoalTarget,
			t
		);

	if (t >= 1.0f)
	{
		isTransition = false;
	}
}

float Camera::Lerp(
	float a,
	float b,
	float t
)
{
	return a + (b - a) * t;
}

VECTOR Camera::LerpVec(
	const VECTOR& a,
	const VECTOR& b,
	float t
)
{
	return VGet(
		Lerp(a.x, b.x, t),
		Lerp(a.y, b.y, t),
		Lerp(a.z, b.z, t)
	);
}
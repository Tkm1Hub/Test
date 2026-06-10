#include "stdafx.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "Time.h"
#include "StageCollision.h"

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
	// カメラモード
	//--------------------------------

	CameraMode newMode;
	
	if (p->GetIsAim())
	{
		newMode = CameraMode::Aim;
	}
	else if (p->GetIsLockOn())
	{
		newMode = CameraMode::LockOn;
	}
	else
	{
		newMode = CameraMode::Normal;
	}

	//--------------------------------
	// モード切り替え検知
	//--------------------------------

	if (newMode != cameraMode)
	{
		StartTransition();

		cameraMode = newMode;
	}

	//--------------------------------
	// カメラ更新
	//--------------------------------

	switch (cameraMode)
	{
	case CameraMode::Aim:
		UpdateAimCamera();
		break;
		
	case CameraMode::LockOn:
		UpdateLockOnCamera();
		break;

	case CameraMode::Normal:
		UpdateNormalCamera();
		break;
	}

	//--------------------------------
	// 補間更新
	//--------------------------------

	if (isTransition)
	{
		UpdateTransition();
	}

	//--------------------------------
	// ステージ当たり判定
	//--------------------------------

	ResolveStageCollision(p->GetCapsuleTop(), pos);

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

	if (p)
	{
		float distance =
			VSize(
				VSub(
					pos,
					p->GetPosition()
				)
			);

		p->UpdateTransparency(distance);
	}
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
	// 基準後方位置
	//--------------------------------

	VECTOR basePos =
		VSub(
			center,
			VScale(dir, cameraDistance)
		);

	basePos.y += LOCKON_HEIGHT;

	//--------------------------------
	// 現在カメラの横ズレ量
	//--------------------------------

	VECTOR toCamera =
		VSub(pos, basePos);

	float side =
		VDot(toCamera, right);

	//--------------------------------
	// 横ズレ制限
	//--------------------------------

	float clampedSide =
		std::clamp(
			side,
			-SIDE_OFFSET,
			SIDE_OFFSET
		);

	//--------------------------------
	// 最終位置
	//--------------------------------

	VECTOR backPos =
		VAdd(
			basePos,
			VScale(right, clampedSide)
		);

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
		SmoothTarget(
			target,
			center,
			0.15f
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

	pos = SmoothTarget(
		pos,
		backPos,
		TRANSITION_TIME
	);

	//--------------------------------
	// target
	//--------------------------------

	target =
		SmoothTarget(
			target,
			enemyPos,
			0.2f
		);

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

void Camera::InputAngle()
{
	float dt = Time::GetInstance().GetDeltaTime() * 60;

	float stickX = Input::GetInput().GetRightStickX();

	float stickY = Input::GetInput().GetRightStickY();

	//--------------------------------
	// 感度
	//--------------------------------

	float horizontalSensitivity = SENSITIVITY_H;

	float verticalSensitivity = SENSITIVITY_V;

	//-------------------------------- 
	// 横回転 
	//--------------------------------

	angleH += stickX * horizontalSensitivity * dt;

	//-------------------------------- 
	// 縦回転 
	//--------------------------------

	angleV -= stickY * verticalSensitivity * dt;

	//-------------------------------- 
	// 縦制限 
	//--------------------------------

	float limit = DX_PI_F / 2.0f - 0.2f;

	if (angleV > limit)
	{
		angleV = limit;
	}

	if (angleV < -limit)
	{
		angleV = -limit;
	}
}

void Camera::FixCameraPosition()
{
	//--------------------------------
	// 回転だけ補間
	//--------------------------------

	float rotateSpeed = 0.15f;

	currentAngleH += (angleH - currentAngleH) * rotateSpeed;

	currentAngleV += (angleV - currentAngleV) * rotateSpeed;

	//--------------------------------
	// 回転行列
	//--------------------------------

	MATRIX rotY = MGetRotY(currentAngleH);

	MATRIX rotX = MGetRotX(currentAngleV);

	//--------------------------------
	// オフセット計算
	//--------------------------------

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

	//--------------------------------
	// 距離は即反映
	//--------------------------------

	pos =
		VAdd(
			target,
			offset
		);
}


void Camera::StartTransition()
{
	isTransition = true;

	transitionTimer = 0.0f;

	transitionStartPos = pos;
	transitionStartTarget = target;
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

	//--------------------------------
	// EaseOutCubic
	//--------------------------------

	t =
		1.0f -
		powf(1.0f - t, 3.0f);

	//--------------------------------
	// 補間
	//--------------------------------

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

VECTOR Camera::SmoothTarget(
	const VECTOR& current,
	const VECTOR& destination,
	float speed
)
{
	return VAdd(
		current,
		VScale(
			VSub(destination, current),
			speed
		)
	);
}

void Camera::ResolveStageCollision(
	const VECTOR& playerPos,
	VECTOR& cameraPos
)
{
	auto hit =
		MV1CollCheck_Line(
			StageCollision::GetInstance().GetCollisionModelHandle(),
			-1,
			playerPos,
			cameraPos
		);

	if (hit.HitFlag)
	{
		VECTOR dir =
			VNorm(
				VSub(cameraPos, playerPos)
			);

		cameraPos =
			VSub(
				hit.HitPosition,
				VScale(dir, CAMERA_HIT_RADIUS)
			);
	}
}
#pragma once
#include "Object.h"

enum class CameraMode
{
	Normal,
	LockOn,
	Aim
};

class Player;

class Camera : public Object
{
public:
	void Init() override;
	void Update() override;

	void SetPlayer(const std::weak_ptr<Player>& playerPtr);

	VECTOR GetFoward() const { return forward; }

private:
	std::weak_ptr<Player> player;

	//==============================
	// 定数
	//==============================

	static constexpr float CAMERA_NEAR = 5.0f;
	static constexpr float CAMERA_FAR = 2000.0f;

	static constexpr float LOOK_OFFSET_Y = 50.0f;

	// 通常カメラ
	static constexpr float DISTANCE_OFFSET = 130.0f;
	static constexpr float SENSITIVITY_H = 0.04f;
	static constexpr float SENSITIVITY_V = 0.02f;

	// ロックオン
	static constexpr float LOCKON_BASE_DISTANCE = 100.0f;
	static constexpr float LOCKON_MAX_DISTANCE = 350.0f;
	static constexpr float LOCKON_HEIGHT = 45.0f;

	// エイム
	static constexpr float AIM_BASE_DISTANCE = 60.0f;
	static constexpr float AIM_HEIGHT = 0.0f;

	// 横ずらし
	static constexpr float SIDE_OFFSET = 80.0f;
	static constexpr float SIDE_AIM_OFFSET = 30.0f;

	// 補間
	static constexpr float SMOOTH_SPEED = 0.1f;

	// 切り替え補間
	static constexpr float TRANSITION_TIME = 0.3f;

	// 押し出し距離
	static constexpr float CAMERA_HIT_RADIUS = 1.5f;

	//==============================
	// カメラ状態
	//==============================

	VECTOR target = VGet(0, 0, 0);
	VECTOR forward = VGet(0, 0, 0);

	float angleV = 0.0f;
	float angleH = 0.0f;

	float currentAngleV = 0.0f;
	float currentAngleH = 0.0f;

	// ロックオン状態保存
	bool prevLockOn = false;

	// 横方向
	int sideSign = 1;

	// モード
	CameraMode cameraMode = CameraMode::Normal;

	//==============================
	// 補間
	//==============================

	bool isTransition = false;

	float transitionTimer = 0.0f;

	VECTOR transitionStartPos;
	VECTOR transitionStartTarget;

	VECTOR transitionGoalPos;
	VECTOR transitionGoalTarget;

	//==============================
	// 関数
	//==============================

	void UpdateNormalCamera();
	void UpdateLockOnCamera();
	void UpdateAimCamera();

	void InputAngle();

	void FixCameraPosition();

	void StartTransition();

	void UpdateTransition();

	float Lerp(float a, float b, float t);

	VECTOR LerpVec(
		const VECTOR& a,
		const VECTOR& b,
		float t
	);

	VECTOR SmoothTarget(
		const VECTOR& current,
		const VECTOR& destination,
		float speed
	);

	void ResolveStageCollision(
		const VECTOR& targetPos,
		VECTOR& cameraPos
	);
};
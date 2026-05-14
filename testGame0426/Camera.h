#pragma once
#include "Object.h"
class Player;
class Camera :public Object
{
public:
	void Init() override;

	void Update() override;

	void SetPlayer(const std::weak_ptr<Player>& playerPtr);

	VECTOR GetFoward() { return forward; }
private:
	std::weak_ptr<Player> player;

	// 定数
	static constexpr float CAMERA_NEAR = 10.0f;
	static constexpr float CAMERA_FAR = 3000.0f;

	static constexpr float SMOOTHING = 0.1f;
	static constexpr float SHAKE_INTARVAL = 0.02f;

	static constexpr float MAX_ANGLE_SPEED = 0.045f;
	static constexpr float ANGLESPEED = 0.035f;

	static constexpr float ACCEL = 0.012f;
	static constexpr float DECEL = 0.006f;

	static constexpr float LOOK_OFFSET_Y = 36.0f;
	static constexpr float DISTANCE_OFFSET = 150.0f;

	VECTOR target = VGet(0.0f, 0.0f, 0.0f);				// 注視点
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);			// カメラ方向ベクトル
	float angleV = 0.0f;								// 垂直角度
	float angleH = 0.0f;								// 水平角度
	float currentAngleSpeed = 0.0f;						// 現在のカメラ旋回速度
	bool isMove = false;								// カメラ移動フラグ

	void InputAngle();
	float CalcAngleSpeed();
	void FixCameraPosition();
};
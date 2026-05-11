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
	static constexpr float CAMERA_FAR = 500.0f;
	static constexpr float SMOOTHING = 0.1f;			// カメラのスムージング
	static constexpr float SHAKE_INTARVAL = 0.02f;		// 揺れ更新の間隔
	static constexpr float MAX_ANGLE_SPEED = 0.04f;		// 最大旋回速度
	static constexpr float ANGLESPEED = 0.03f;			// カメラ感度
	static constexpr float ACCEL = 0.01f;				// カメラ加速度
	static constexpr float DECEL = 0.005f;				// カメラ減速度
	static constexpr float LOOK_OFFSET_Y = 10.0f;		// 注視点の高さ
	static constexpr float DISTANCE_OFFSET = 30.0f;		// プレイヤーからの距離

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
#pragma once
#include "Object.h"

class Camera;
class Player :public Object
{
public:
	int HP;			// 体力
	int Energy;		// 射撃用エネルギー

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetCamera(const std::weak_ptr<Camera>& cameraPtr);

	const VECTOR& GetModelForward() const { return modelFoward; }

private:

	float Accel = 0.035f;				// 移動加速度
	float Decel = 0.9f;				// 移動減速度
	float MaxMoveSpeed = 0.7;			// 最大移動速度

	std::weak_ptr<Camera> camera;

	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);
	VECTOR moveVelocity = VGet(0.0f, 0.0f, 0.0f);		// x,z方向移動速度
	float verticalVelocity = 0.0f;	// 垂直方向速度
	VECTOR modelFoward = VGet(0.0f, 0.0f, 0.0f);

	float currentMoveSpeed = 0.0f;
	bool isMove;


	void PlayerMove();
	void culcMoveSpeed(const VECTOR& input);
	VECTOR GetMoveInput();		// スティックによる移動ベクトルの取得
};
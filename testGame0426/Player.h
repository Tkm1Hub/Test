#pragma once
#include "Object.h"
#include "StateMachine.h"
#include "PlayerParameter.h"

class Camera;
class PlayerStateBase;
class Player :public Object
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void SetCamera(const std::weak_ptr<Camera>& cameraPtr);

	void ChangeState(std::shared_ptr<PlayerStateBase>a_spState);		// ステート変更

	const VECTOR& GetModelForward() const { return modelFoward; }
	const VECTOR& GetInputDir() const { return input; }

	void MoveInput();		// スティックによる移動入力

	float GetJumpPower() const { return JumpPower; }
	PlayerParameter GetParam() const { return param; }

private:
	StateMachine stateMachine;			// ステートマシン
	PlayerParameter param;				// パラメーター

	float Accel = 0.04f;				// 移動加速度
	float Decel = 0.88f;				// 移動減速度
	float MaxMoveSpeed = 0.6f;			// 最大移動速度
	float JumpPower = 0.8f;				// ジャンプ力

	std::weak_ptr<Camera> camera;

	VECTOR input = VGet(0.0f, 0.0f, 0.0f);				// 移動入力
	VECTOR modelFoward = VGet(0.0f, 0.0f, 0.0f);

	float currentMoveSpeed = 0.0f;
	bool isMove;


	void ApplyVelocity();
	void culcMoveSpeed();
	void RotateCharacter();
};
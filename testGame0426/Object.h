#pragma once
#include "stdafx.h"
#include "StateMachine.h"

class StateMachine;
class Object
{
public:
	virtual void Init(){}		// 初期化
	virtual void Update(){}		// 更新
	virtual void Draw();		// 描画

	virtual ~Object(){}

	// 取得関数
	VECTOR GetPosition() const { return pos; }
	VECTOR GetForward() const { return forward; }
	VECTOR GetScale() const { return scale; }
	bool GetIsActive() const { return isActive; }
	bool GetIsDestoroy() const { return isDestroy; }
	bool isCollision() const { return isCollisionEnabled; }
	float GetVerticalVelocity() const { return verticalVelocity; }
	VECTOR GetExternalVelocity() const { return externalVelocity; }
	VECTOR GetMoveVelocity() const { return moveVelocity; }
	const VECTOR& GetMoveDir() const { return moveDir; }

	void SetMoveVelocity(VECTOR velocity) { moveVelocity = velocity; }
	void SetExternalVelocity(VECTOR velocity) { externalVelocity = velocity; }
	void SetVerticalVelocity(float velocity) { verticalVelocity = velocity; }
	void SetIsGraund(bool flag) { isGround = flag; }

protected:
	float moveAccel = 0.04f;
	float moveDecel = 0.88f;

	float angleSpeed = 0.5f;
	float gravity = 0.04f;

	StateMachine stateMachine;					// ステートマシン
	int modelHandle = -1;						// モデルハンドル

	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);		// 座標
	VECTOR moveDir = VGet(0.0f, 0.0f, 0.0f);	// 移動方向
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);	// 前方
	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);		// モデルサイズ

	VECTOR moveVelocity = VGet(0.0f, 0.0f, 0.0f);		// 移動速度
	VECTOR externalVelocity = VGet(0.0f, 0.0f, 0.0f);	// 外的影響速度
	float  verticalVelocity = 0.0f;						// 垂直速度

	float maxMoveSpeed = 0.0f;				// 最大移動速度

	bool isActive = true;					// 有効フラグ
	bool isDestroy = false;					// 削除フラグ
	bool isCollisionEnabled = true;			// 当たり判定フラグ
	bool isMove = false;					// 移動フラグ
	bool isGround = false;					// 着地フラグ

	void ApplyVelocity();
	void CalcMoveSpeed();
	void RotateAngle();
	void ApplyGravity();		// 重力適応
};
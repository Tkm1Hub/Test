#pragma once
#include "stdafx.h"
#include "StateMachine.h"
#include "DamageInfo.h"

class StateMachine;
class Object : public std::enable_shared_from_this<Object>
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
	bool GetIsCollision() const { return isCollisionEnabled; }
	float GetVerticalVelocity() const { return verticalVelocity; }
	VECTOR GetExternalVelocity() const { return externalVelocity; }
	VECTOR GetMoveVelocity() const { return moveVelocity; }
	const VECTOR& GetMoveDir() const { return moveDir; }
	//カプセル
	VECTOR GetCapsuleBottom() const;
	VECTOR GetCapsuleTop() const;
	VECTOR GetCapsuleCenter() const;
	VECTOR GetFootPosition() const;
	float GetBodyRadius() const { return bodyRadius; }
	float GetBodyHeight() const { return bodyHeight; }

	// 衝突
	virtual void OnHit(const DamageInfo& info) {};

	void SetMoveVelocity(const VECTOR& velocity) { moveVelocity = velocity; }
	void SetExternalVelocity(const VECTOR& velocity) { externalVelocity = velocity; }
	void AddVerticalVelocity(float power);

	void SetLookDir(const VECTOR& dir) { lookDir = dir; }
	void SetIsGraund(bool flag) { isGround = flag; }

protected:
	float moveAccel = 0.14f;
	float moveDecel = 0.8f;
	float angleSpeed = 0.5f;
	float gravity = 0.5;

	StateMachine stateMachine;					// ステートマシン
	int modelHandle = -1;						// モデルハンドル

	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);		// 座標
	VECTOR moveDir = VGet(0.0f, 0.0f, 0.0f);	// 移動方向
	VECTOR lookDir = VGet(0.0f, 0.0f, 1.0f);	// 向きたい方向
	VECTOR forward = VGet(0.0f, 0.0f, 1.0f);	// 現在向いている方向
	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);		// モデルサイズ

	VECTOR moveVelocity = VGet(0.0f, 0.0f, 0.0f);		// 移動速度
	VECTOR externalVelocity = VGet(0.0f, 0.0f, 0.0f);	// 外的影響速度
	float  verticalVelocity = 0.0f;						// 垂直速度

	float maxMoveSpeed = 0.0f;				// 最大移動速度
	float bodyRadius = 0.0f;				// 当たり判定半径
	float bodyHeight = 0.0f;					// 当たり判定高さ

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
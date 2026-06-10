#pragma once
#include "stdafx.h"
#include "StateMachine.h"

class StateMachine;
class Object : public std::enable_shared_from_this<Object>
{
public:
	virtual void Init(){}		// 初期化
	virtual void Update(){}		// 更新
	virtual void Draw();		// 描画

	virtual ~Object(){}

	// 取得関数
	int GetModelHandle() const { return modelHandle; }
	VECTOR GetPosition() const { return pos; }
	VECTOR GetForward() const { return forward; }
	VECTOR GetScale() const { return scale; }
	float GetAlpha() const { return alpha; }
	bool GetIsActive() const { return isActive; }
	bool GetIsDestoroy() const { return isDestroy; }
	bool GetIsCollision() const { return isCollisionEnabled; }
	float GetVerticalVelocity() const { return verticalVelocity; }
	VECTOR GetExternalVelocity() const { return externalVelocity; }
	VECTOR GetMoveVelocity() const { return moveVelocity; }
	const VECTOR& GetMoveDir() const { return moveDir; }
	bool GetIsGround()const { return isGround; }

	void SetMaxMoveSpeed(const float speed) { maxMoveSpeed = speed; }
	void SetPosition(const VECTOR& newPos) { pos = newPos; }
	void SetMoveVelocity(const VECTOR& velocity) { moveVelocity = velocity; }
	void SetExternalVelocity(const VECTOR& velocity) { externalVelocity = velocity; }
	void SetIsGround(bool flag) { isGround = flag; }
	void AddVerticalVelocity(float power);

	void SetLookDir(const VECTOR& dir) { lookDir = dir; }
	void SetIsCollisionEnabled(bool flag) { isCollisionEnabled = flag; }
	void Destroy() { isDestroy = true; }

protected:
	float moveAccel = 0.14f;
	float moveDecel = 0.8f;
	float extDecel = 0.9f;
	float angleSpeed = 0.5f;
	float gravity = 0.2f;
	float alpha = 1.0f;

	bool isFadeIn = false;
	bool isFadeOut = false;

	float fadeSpeed = 0.05f;

	void StartFadeIn();
	void StartFadeOut();
	void UpdateFade();

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

	bool isActive = true;					// 有効フラグ
	bool isDestroy = false;					// 削除フラグ
	bool isCollisionEnabled = true;			// 当たり判定フラグ
	bool isMove = false;					// 移動フラグ
	bool isGround = false;					// 着地フラグ
	bool wasGround = false;

	void ApplyVelocity();
	void CalcMoveSpeed();
	void RotateAngle();
	void ApplyGravity();		// 重力適応
};
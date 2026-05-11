#pragma once
#include "stdafx.h"
#include "StateMachine.h"
class StateMachine;
class Object
{
public:
	virtual void Init(){}		// 初期化
	virtual void Update(){}		// 更新
	virtual void Draw(){}		// 描画

	virtual ~Object(){}

	void ApplyGravity();		// 重力適応

	// 取得関数
	VECTOR GetPosition() const { return pos; }
	VECTOR GetRotation() const { return rot; }
	VECTOR GetScale() const { return scale; }
	bool GetIsActive() const { return isActive; }
	bool GetIsDestoroy() const { return isDestroy; }
	bool isCollision() const { return isCollisionEnabled; }

	void SetIsGraund(bool flag) { isGround = flag; }

protected:
	static constexpr float GRAVITY = 0.04f;	// 重力

	StateMachine stateMachine;					// ステートマシン
	int modelHandle = -1;						// モデルハンドル

	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);		// 座標
	VECTOR rot = VGet(0.0f, 0.0f, 0.0f);		// 回転
	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);		// モデルサイズ

	VECTOR moveVelocity = VGet(0.0f, 0.0f, 0.0f);	// 移動速度
	float  verticalVelocity = 0.0f;					// 垂直速度

	bool isActive = true;					// 有効フラグ
	bool isDestroy = false;					// 削除フラグ
	bool isCollisionEnabled = true;			// 当たり判定フラグ
	bool isGround = false;					// 着地フラグ
};
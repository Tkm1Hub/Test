#pragma once
#include "stdafx.h"

class Object
{
public:
	virtual void Init(){}		// 初期化
	virtual void Update(){}		// 更新
	virtual void Draw(){}		// 描画

	virtual ~Object(){}

	// 取得関数
	VECTOR GetPosition() const { return pos; }
	VECTOR GetRotation() const { return rot; }
	VECTOR GetScale() const { return scale; }
	bool GetIsActive() const { return isActive; }
	bool GetIsDestoroy() const { return isDestroy; }
	bool isCollision() const { return isCollisionEnabled; }

protected:
	int modelHandle = -1;						// モデルハンドル

	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);		// 座標
	VECTOR nextPos = VGet(0.0f, 0.0f, 0.0f);	// 移動先の座標
	VECTOR rot = VGet(0.0f, 0.0f, 0.0f);		// 回転
	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);		// モデルサイズ

	bool isActive = true;					// 有効フラグ
	bool isDestroy = false;					// 削除フラグ
	bool isCollisionEnabled = true;			// 当たり判定フラグ
};
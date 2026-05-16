#pragma once
#include "DxLib.h"

class UIBase
{
public:
	virtual ~UIBase() = default;

	virtual void Init(){}
	virtual void Update(){}
	virtual void Draw(){}

	bool GetIsDestroy() const { return isDestroy; }
	bool GetIsActive() const { return isActive; }
protected:
	bool isDestroy = false;
	bool isActive = false;

	// Zç¿ïWÇÕégÇÌÇ»Ç¢
	VECTOR screenPos = VGet(0.0f, 0.0f, 0.0f);
};
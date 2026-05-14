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
protected:
	bool isDestroy = false;

	// Zç¿ïWÇÕégÇÌÇ»Ç¢
	VECTOR ScreenPos = VGet(0.0f, 0.0f, 0.0f);
};
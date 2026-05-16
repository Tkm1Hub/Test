#pragma once
#include "DxLib.h"

class Object;
struct DamageInfo
{
	int damage = 0;
	float stunPower = 0;
	VECTOR hitDir = VGet(0.0f, 0.0f, 0.0f);
	float knockBackPower = 0.0f;
	Object* attacker = nullptr;
};
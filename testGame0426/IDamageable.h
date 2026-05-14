#pragma once
#include "DxLib.h"
class IDamageable
{
public:
	virtual ~IDamageable() = default;

	virtual int GetHP() const = 0;
	virtual int GetMaxHP() const = 0;
	virtual void TakeDamage(int damage) = 0;
};
#pragma once
#include "IDamageable.h"
#include "Object.h"

class DamageableObject :
	public IDamageable,
	public Object
{
public:
	int GetHP() const override { return HP; }

	int GetMaxHP() const override { return MaxHP; }

	void TakeDamage(int damage) override
	{
		HP -= damage;
		if (HP < 0) HP = 0;
	}

protected:
	int HP = 0;
	int MaxHP = 0;
};
#pragma once
#include "IDamageable.h"
#include "Object.h"
#include "DamageInfo.h"

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

	// Õ“Ë
	virtual void OnHit(const DamageInfo& info)
	{
		lastDamageInfo = info;
	}

	// ƒ_ƒ[ƒWî•ñ‚ðŽæ“¾
	const DamageInfo& GetLastDamageInfo() const { return lastDamageInfo; }

protected:
	int HP = 0;
	int MaxHP = 0;
	DamageInfo lastDamageInfo;
};
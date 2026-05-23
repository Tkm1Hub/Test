#pragma once
#include <vector>

enum class DamageType
{
	Melee,
	Projectile
};

struct AttackStep
{
	float windupTime;
	float activeTime;
	float recoveryTime;

	int damage;

	float stunPower;

	float attackMoveSpeed;

	float attackHitRadius;

	float attackForwardOffset;

	float knockBackPower;

	DamageType type;
};

struct AttackData
{
	std::vector<AttackStep> combo;
};

enum class AttackPhase
{
	Windup,
	Active,
	Recovery
};

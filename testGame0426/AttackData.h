#pragma once
#include <vector>

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
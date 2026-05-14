#pragma once
#include <vector>

struct AttackStep
{
	float windupTime;
	float activeTime;
	float recoveryTime;

	int damage;
	float attackMoveSpeed;
	float attackHitRadius;
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
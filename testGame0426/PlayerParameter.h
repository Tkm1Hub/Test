#pragma once

struct PlayerParameter
{
	float moveAccel = 0.04f;
	float moveDecel = 0.88f;
	float maxMoveSpeed = 0.6f;

	float jumpPower = 0.8f;

	float dodgeSpeed = 3.0f;
	float angleSpeed = 0.5f;

	int attackPower = 10;

	float dodgeTime = 0.35;
};
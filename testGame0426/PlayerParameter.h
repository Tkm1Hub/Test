#pragma once

struct PlayerParameter
{
	float moveAccel = 0.04f;
	float moveDecel = 0.88f;
	float maxMoveSpeed = 0.6f;

	float jumpPower = 0.8f;

	float dodgeSpeed = 1.2f;
	float angleSpeed = 0.5f;

	int attackPower = 10;
};
#pragma once

struct PlayerParameter
{
	// ===== 基本 =====
	int HP = 100;
	int attackPower = 12;
	int stunPower = 30;

	//　===== 移動 =====
	float moveAccel = 0.14f;
	float moveDecel = 0.84f;
	float maxMoveSpeed = 3.6f;
	float jumpPower = 8.0f;
	float angleSpeed = 0.22f;

	// ===== 攻撃 =====
	float windupTime = 0.0f;		// 予備動作時間 
	float activeTime = 12.0f;       // 攻撃時間
	float recoveryTime = 6.0f;		// 後隙時間

	float attackForwardOffset = 18.0f;		// 攻撃位置のオフセット
	float attackMoveSpeed = 8.0f;			// 攻撃移動速度
	float attackHitRadius = 20.0f;			// HitSphere半径

	// ===== ダメージ =====
	float damageTime = 4.0f;		// 被ダメージ硬直時間

	// ===== 回避 =====
	float dodgeSpeed = 15.0f;
	float dodgeTime = 0.35f;

	// ===== 当たり判定 =====
	float bodyRadius = 8.0f;
	float bodyHeight = 32.0f;

	// ===== コンボ =====
	std::vector<AttackStep> combo =
	{
		// 1段目
		{
			.windupTime = 2.0f,
			.activeTime = 20.0f,
			.recoveryTime = 20.0f,

			.damage = 8,
			.stunPower = 12.0f,

			.attackMoveSpeed = 7.0f,
			.attackHitRadius = 18.0f,
			.attackForwardOffset = 18.0f,

			.knockBackPower = 6.0f
		},
		// 2段目
		{
			.windupTime = 2.0f,
			.activeTime = 5.0f,
			.recoveryTime = 6.0f,

			.damage = 10,
			.stunPower = 14.0f,

			.attackMoveSpeed = 7.5f,
			.attackHitRadius = 20.0f,
			.attackForwardOffset = 18.0f,

			.knockBackPower = 8.0f
		},
		// 3段目
		{
			.windupTime = 3.0f,
			.activeTime = 6.0f,
			.recoveryTime = 8.0f,

			.damage = 14,
			.stunPower = 18.0f,

			.attackMoveSpeed = 8.0f,
			.attackHitRadius = 22.0f,
			.attackForwardOffset = 20.0f,

			.knockBackPower = 10.0f
		},
		// 4段目
		{
			.windupTime = 4.0f,
			.activeTime = 6.0f,
			.recoveryTime = 10.0f,

			.damage = 18,
			.stunPower = 24.0f,

			.attackMoveSpeed = 9.0f,
			.attackHitRadius = 24.0f,
			.attackForwardOffset = 24.0f,

			.knockBackPower = 14.0f
		},
		// 5段目
		{
			.windupTime = 6.0f,
			.activeTime = 8.0f,
			.recoveryTime = 16.0f,

			.damage = 28,
			.stunPower = 40.0f,

			.attackMoveSpeed = 30.0f,
			.attackHitRadius = 30.0f,
			.attackForwardOffset = 32.0f,

			.knockBackPower = 24.0f
		}
	};
};
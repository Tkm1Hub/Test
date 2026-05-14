#pragma once

struct PlayerParameter
{
	// ===== 基本 =====
	int HP = 100;
	int attackPower = 12;

	//　===== 移動 =====
	float moveAccel = 0.14f;
	float moveDecel = 0.84f;
	float maxMoveSpeed = 3.6f;
	float jumpPower = 8.0f;
	float angleSpeed = 0.22f;

	// ===== 攻撃 =====
	float windupTime = 0.0f;       // 予備動作時間 
	float activeTime = 12.0f;       // 攻撃時間
	float recoveryTime = 6.0f;     // 後隙時間

	float attackForwardOffset = 18.0f;   // 攻撃位置のオフセット
	float attackMoveSpeed = 8.0f;       // 攻撃移動速度
	float attackHitRadius = 20.0f;       // HitSphere半径
	
	// ===== 回避 =====
	float dodgeSpeed = 15.0f;
	float dodgeTime = 0.35f;

	// ===== 当たり判定 =====
	float bodyRadius = 8.0f;
	float bodyHeight = 32.0f;
};
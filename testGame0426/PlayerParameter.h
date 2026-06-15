#pragma once
#include "DxLib.h"
#include "AttackData.h"

struct PlayerParameter
{
	// ===== 基本 =====
	int HP{};
	int BulletNum{};
	int attackPower{};
	int stunPower{};
	VECTOR scale{};

	// ===== 移動 =====
	float moveAccel{};
	float moveDecel{};
	float maxMoveSpeed{};
	float jumpPower{};
	float angleSpeed{};

	// ===== エイム =====
	float aimTriggerDeadZone{};
	float fireTriggerDeadZone{};
	float fireKnockBackPower{};

	// ===== 攻撃 =====
	float windupTime{};			// 予備動作時間
	float activeTime{};			// 攻撃時間
	float recoveryTime{};		// 後隙時間

	float attackForwardOffset{};	// 攻撃位置のオフセット
	float attackMoveSpeed{};		// 攻撃移動速度
	float attackHitRadius{};		// HitSphere半径

	float SearchEnemyDistance{};	// 敵検索距離

	// ===== ダメージ =====
	float damageTime{};			// 被ダメージ硬直時間

	// ===== 回避 =====
	float dodgeSpeed{};
	float dodgeTime{};

	// ===== 当たり判定 =====
	float bodyRadius{};
	float bodyHeight{};
	float extraHitRadius{};

	// ===== 射撃 =====
	AttackStep bullet{};

	float bulletSpeed{};

	// ===== コンボ =====
	std::vector<AttackStep> combo{};

	// ===== SP攻撃 =====
	std::vector<AttackStep> SPAttack{};
};
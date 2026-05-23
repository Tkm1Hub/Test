#pragma once

struct PlayerParameter
{
	// ===== 基本 =====
	int HP = 100;
	int BulletNum = 3;
	int attackPower = 12;
	int stunPower = 30;

	//　===== 移動 =====
	float moveAccel = 0.14f;
	float moveDecel = 0.84f;
	float maxMoveSpeed = 3.6f;
	float jumpPower = 8.0f;
	float angleSpeed = 0.22f;

	// ===== エイム =====
	float aimTriggerDeadZone = 0.3f;
	float fireTriggerDeadZone = 0.5f;
	float fireKnockBackPower = 12.0f;

	// ===== 攻撃 =====
	float windupTime = 0.0f;		// 予備動作時間 
	float activeTime = 12.0f;       // 攻撃時間
	float recoveryTime = 6.0f;		// 後隙時間

	float attackForwardOffset = 18.0f;		// 攻撃位置のオフセット
	float attackMoveSpeed = 8.0f;			// 攻撃移動速度
	float attackHitRadius = 20.0f;			// HitSphere半径

	float SearchEnemyDistance = 360.0f;	// 敵検索距離

	// ===== ダメージ =====
	float damageTime = 4.0f;		// 被ダメージ硬直時間

	// ===== 回避 =====
	float dodgeSpeed = 20.0f;
	float dodgeTime = 0.35f;

	// ===== 当たり判定 =====
	float bodyRadius = 8.0f;
	float bodyHeight = 32.0f;
	float extraHitRadius = 32.0f;

	// ===== 射撃 =====
	AttackStep bullet =
	{
		20.0f, // windupTime
		8.0f,  // activeTime
		20.0f, // recoveryTime
		20,    // damage
		50.0f, // stunPower
		6.0f,  // attackMoveSpeed
		18.0f, // attackHitRadius
		16.0f, // attackForwardOffset
		30.0f  // knockBackPower
	};

	float bulletSpeed = 35.0f;

	// ===== コンボ =====
	std::vector<AttackStep> combo =
	{
		// 1段目：出が早い（発生最速、隙も小さく牽制に最適）
		{
			.windupTime = 5.0f,         // 発生を最速に
			.activeTime = 15.0f,         // サッと振る
			.recoveryTime = 5.0f,       // 次の段へコンボ移行しやすいよう後隙は短め

			.damage = 6,                // 低
			.stunPower = 3.0f,         // 中（しっかり怯ませてコンボを繋ぐ）

			.attackMoveSpeed = 5.0f,
			.attackHitRadius = 16.0f,
			.attackForwardOffset = 14.0f,

			.knockBackPower = 12.0f      // 敵が離れすぎないように低め
		},
		// 2段目：繋ぎ（1段目の勢いを維持しつつ、流れるように繋ぐ）
		{
			.windupTime = 8.0f,
			.activeTime = 15.0f,
			.recoveryTime = 8.0f,

			.damage = 10,               // 中
			.stunPower = 5.0f,         // 中

			.attackMoveSpeed = 6.0f,
			.attackHitRadius = 18.0f,
			.attackForwardOffset = 16.0f,

			.knockBackPower = 12.0f
		},
		// 3段目：前進強い（大きく踏み込んで間合いを詰める、または敵を押し込む）
		{
			.windupTime = 12.0f,
			.activeTime = 15.0f,
			.recoveryTime = 12.0f,

			.damage = 14,               // 中
			.stunPower = 7.0f,         // 高（相手の強靭を削るイメージ）

			.attackMoveSpeed = 16.0f,   // ★前進力を大幅強化（グッと踏み込む）
			.attackHitRadius = 22.0f,   // 踏み込む分、判定も少し広めに
			.attackForwardOffset = 24.0f, // 前方に判定を突き出す

			.knockBackPower = 12.0f
		},
		// 4段目：隙大きめ（5段目への大振りの溜め。威力・疲労が高いが外すと危険）
		{
			.windupTime = 15.0f,         // ★前振りを長くして「大振り感」を演出
			.activeTime = 15.0f,
			.recoveryTime = 18.0f,      // ★後隙を大きく（コンボを止めると隙だらけ）

			.damage = 22,               // 高
			.stunPower = 10.0f,         // 高

			.attackMoveSpeed = 8.0f,
			.attackHitRadius = 26.0f,
			.attackForwardOffset = 24.0f,

			.knockBackPower = 12.0f
		},
		// 5段目：フィニッシュ（一撃必殺。4段目の大きな隙から放たれる超ド級の一撃）
		{
			.windupTime = 20.0f,        // ★最大級のタメ（ヒットストップやエフェクトが映える時間）
			.activeTime = 15.0f,
			.recoveryTime = 25.0f,      // 全力を出し切った後の大きな戻りモーション

			.damage = 45,               // 超高
			.stunPower = 20.0f,         // 超高（確定でダウンを奪えるレベル）

			.attackMoveSpeed = 20.0f,   // 最後の押し込み
			.attackHitRadius = 35.0f,   // 巻き込みを広く（超広範囲）
			.attackForwardOffset = 30.0f,

			.knockBackPower = 35.0f     // ★超強力な吹き飛ばし
		}
	};
};
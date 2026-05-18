#pragma once
#include "EnemyParameter.h"

struct EnemyMeleeParameter : EnemyParameter
{
	EnemyMeleeParameter()
	{
        // ===== 基本 =====
        HP = 60;
        attackPower = 15;

        // ===== 移動 =====
        chaseSpeed = 2.4f;
        accel = 0.1f;
        decel = 0.88f;
        rotateSpeed = 0.12f;

        // ===== 索敵 =====
        searchRange = 220.0f;      // プレイヤー発見距離
        lostRange = 320.0f;        // 見失う距離

        // ===== 攻撃 =====
        windupTime = 45.0f;       // 予備動作時間 
        activeTime = 12.0f;       // 攻撃時間
        recoveryTime = 40.0f;     // 後隙時間

        damage = 10;                    // ダメージ
        attackForwardOffset = 18.0f;   // 攻撃位置のオフセット
        attackMoveSpeed = 6.0f;       // 攻撃移動速度
        attackHitRadius = 20.0f;       // HitSphere半径

        attackRange = 60.0f;        // 攻撃開始距離

        // ===== ダメージ =====
        damageTime = 20.0f;           // 被弾硬直時間

        // ===== 回避/ノックバック =====
        knockBackPower = 4.0f;
        weight = 1.0f;

        // ===== ジャンプ =====
        gravity = 0.03f;
        maxFallSpeed = 1.0f;

        // ===== 当たり判定 =====
        bodyRadius = 8.0f;
        bodyHeight = 24.0f;

        // ===== コンボ =====
        combo =
        {
            {
                .windupTime = 35.0f,
                .activeTime = 10.0f,
                .recoveryTime = 45.0f,

                .damage = 12,
                .stunPower = 0.0f,

                .attackMoveSpeed = 5.0f,
                .attackHitRadius = 18.0f,
                .attackForwardOffset = 18.0f,

                .knockBackPower = 8.0f
            }
        };
    }
};
#pragma once
#pragma once
#include "EnemyParameter.h"

struct EnemyShooterParameter : EnemyParameter
{
    EnemyShooterParameter()
    {
        // ===== 基本 =====
        HP = 80;
        attackPower = 10;

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
        recoveryTime = 70.0f;     // 後隙時間

        damage = 10;                    // ダメージ
        attackForwardOffset = 18.0f;   // 攻撃位置のオフセット
        attackMoveSpeed = 0.0f;       // 攻撃移動速度
        attackHitRadius = 5.0f;       // HitSphere半径

        attackRange = 60.0f;        // 攻撃開始距離

        // ===== ダメージ =====
        damageTime = 20.0f;           // 被弾硬直時間

        // ===== 耐性 =====
        meleeDamageRate = 1.5f;             // 物理耐性
        meleeStunRate = 1.0f;               // 物理スタン耐性
        projectileDamageRate = 0.6f;        // 射撃耐性
        prijectileStunRate = 1.8f;          // 射撃スタン耐性

        // ===== スタン =====
        maxStunGauge = 100.0f;      // 最大スタン値
        stunTime = 600.0f;          // スタン硬直時間

        // ===== 回避/ノックバック =====
        knockBackPower = 4.0f;
        weight = 1.0f;

        // ===== 当たり判定 =====
        bodyRadius = 8.0f;
        bodyHeight = 8.0f;

        // ===== コンボ =====
        combo =
        {
            {
                // windup
                50.0f,

                // active
                6.0f,

                // recovery
                15.0f,

                // damage
                10,

                // stunPower
                12.0f,

                // attackMoveSpeed
                0.0f,

                // attackHitRadius
                10.0f,

                // attackForwardOffset
                16.0f,

                // knockBackPower
                4.0f
            }

        };
    }

    float keepDistance = 300.0f;        // プレイヤーからとる距離
    float toleranceDistance = 50.0f;    // 許容範囲
    float bulletSpeed = 7.0f;           // 弾の速度
};
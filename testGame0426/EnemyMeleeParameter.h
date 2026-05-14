#pragma once
struct EnemyMeleeParameter
{
    // ===== 基本 =====
    int maxHP = 40;
    int attackPower = 12;

    // ===== 移動 =====
    float maxMoveSpeed = 2.4f;
    float accel = 0.1f;
    float decel = 0.88f;
    float rotateSpeed = 0.12f;

    // ===== 索敵 =====
    float searchRange = 220.0f;      // プレイヤー発見距離
    float lostRange = 320.0f;        // 見失う距離

    // ===== 攻撃 =====
    float windupTime = 45.0f;       // 予備動作時間 
    float activeTime = 12.0f;       // 攻撃時間
    float recoveryTime = 70.0f;     // 後隙時間

    int damage = 10;                    // ダメージ
    float attackForwardOffset = 18.0f;   // 攻撃位置のオフセット
    float attackMoveSpeed = 6.0f;       // 攻撃移動速度
    float attackHitRadius = 20.0f;       // HitSphere半径

    float attackRange = 60.0f;        // 攻撃開始距離

    // ===== 回避/ノックバック =====
    float knockBackPower = 4.0f;
    float weight = 1.0f;

    // ===== ジャンプ =====
    float gravity = 0.03f;
    float maxFallSpeed = 1.0f;

    // ===== 当たり判定 =====
    float bodyRadius = 8.0f;
    float bodyHeight = 24.0f;

};
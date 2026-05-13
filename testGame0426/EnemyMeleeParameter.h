#pragma once
struct EnemyMeleeParameter
{
    // ===== 基本 =====
    int maxHP = 100;
    int attackPower = 10;

    // ===== 移動 =====
    float maxMoveSpeed = 0.4f;
    float accel = 0.02f;
    float decel = 0.90f;
    float rotateSpeed = 0.15f;

    // ===== 索敵 =====
    float searchRange = 25.0f;     // プレイヤー発見距離
    float lostRange = 35.0f;       // 見失う距離

    // ===== 攻撃 =====
    float attackRange = 4.0f;      // 攻撃開始距離
    float attackCooldown = 1.5f;   // 攻撃間隔
    float attackDuration = 0.6f;   // 攻撃時間

    // ===== 回避/ノックバック =====
    float knockBackPower = 0.5f;
    float weight = 1.0f;

    // ===== ジャンプ =====
    float gravity = 0.03f;
    float maxFallSpeed = 1.0f;

    // ===== 当たり判定 =====
    float bodyRadius = 2.0f;
    float bodyHeight = 5.0f;

    // ===== AI =====
    float thinkInterval = 0.2f;

    // ===== ステート時間 =====
    float idleTime = 2.0f;
    float chaseTime = 10.0f;
};
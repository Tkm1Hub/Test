#pragma once
#include "CharacterBase.h"
#include "EnemyParameter.h"
#include "EnemyStateBase.h"
#include "StunComponent.h"
#include "AttackData.h"

class Player;
class Enemy : 
	public CharacterBase,
	public StunComponent
{
public:
	void SetPlayer(const std::weak_ptr<Player>& playerPtr);

	//初期化
	void Init() override;
	
	// 更新
	void Update() override;

	// 攻撃
	virtual void Attack(const AttackStep& step){}

	// 追跡
	virtual void Chase();

	// 被弾
	void OnHit(const DamageInfo& info) override;

	// スタン
	void OnStun() override;

	// 目標地点へ移動
	void MoveTo(const VECTOR& targetPos);

	// ステート変更
	void ChangeState(std::shared_ptr<EnemyStateBase>a_spState);

	// プレイヤーとの距離を取得
	float GetDistanceToPlayer() const;
	
	// プレイヤーへの方向を取得
	VECTOR GetDirectionToPlayer() const;

	// 攻撃可能範囲を取得
	float GetAttackRange() const { return GetParam().attackRange; }

	// 攻撃クールダウン
	float GetAttackCoolDown()const { return attackCooldown; }
	void SetAttackCooldown(float value) { attackCooldown = value; }
	void UpdateAttackCoolDown();

	const AttackData& GetAttackData() { return attackData; }

	virtual void OnParry() {};

	virtual const EnemyParameter& GetParam() const = 0;

protected:
	std::weak_ptr<Player> player;
	float attackCooldown = 0.0f;
};

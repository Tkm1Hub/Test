#pragma once
#include "DamageableObject.h"
#include "EnemyStateBase.h"
#include "AttackData.h"

class Player;
class Enemy : public DamageableObject
{
public:
	void SetPlayer(const std::weak_ptr<Player>& playerPtr);

	void Update() override;

	// 攻撃
	virtual void Attack(const AttackStep& step){}

	// 追跡
	virtual void Chase();

	// 目標地点へ移動
	void MoveTo(const VECTOR& targetPos);

	// ステート変更
	void ChangeState(std::shared_ptr<EnemyStateBase>a_spState);

	// プレイヤーとの距離を取得
	float GetDistanceToPlayer() const;
	
	// プレイヤーへの方向を取得
	VECTOR GetDirectionToPlayer() const;

	// 攻撃可能範囲を取得
	virtual float GetAttackRange() const = 0;

	const AttackData& GetAttackData() { return attackData; }

protected:
	std::weak_ptr<Player> player;
	AttackData attackData;
};

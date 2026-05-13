#pragma once
#include "Object.h"
#include "EnemyStateBase.h"

class Player;
class Enemy : public Object
{
public:
	void SetPlayer(const std::weak_ptr<Player>& playerPtr);

	virtual void Attack(){}		// çUåÇ
	virtual void Chase();		// í«ê’

	void MoveTo(const VECTOR& targetPos);

	void Update() override;

	void ChangeState(std::shared_ptr<EnemyStateBase>a_spState);
protected:
	std::weak_ptr<Player> player;
	
};

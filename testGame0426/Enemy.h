#pragma once
#include "Object.h"
#include "StateMachine.h"
#include "EnemyStateBase.h"

class Enemy : public Object
{
public:
	virtual void Attack(){}		// 攻撃

	void ChangeState(std::shared_ptr<EnemyStateBase>a_spState);
private:
	StateMachine stateMachine;	// ステートマシン
	
	float Accel = 0.04f;				// 移動加速度
	float Decel = 0.88f;				// 移動減速度
	float MaxMoveSpeed = 0.6f;			// 最大移動速度

	VECTOR modelFoward = VGet(0.0f, 0.0f, 0.0f);

	float currentMoveSpeed = 0.0f;
	bool isMove;

	void ApplyVelocity();
	void culcMoveSpeed();
};

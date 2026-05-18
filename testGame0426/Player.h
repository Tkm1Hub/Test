#pragma once
#include "CharacterBase.h"
#include "PlayerParameter.h"
#include "AttackData.h"

class Camera;
class Enemy;
class PlayerStateBase;
class AttackHitSphere;
class Player :	public CharacterBase
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void SetCamera(const std::weak_ptr<Camera>& cameraPtr);

	void ChangeState(std::shared_ptr<PlayerStateBase>a_spState);		// ステート変更

	void MoveInput();		// スティックによる移動入力

	void Attack(const AttackStep& step);	// 近接攻撃

	void OnHit(const DamageInfo& info) override;

	const AttackData& GetAttackData() { return attackData; }

	PlayerParameter& GetParam() { return param; }

	std::weak_ptr<Enemy> GetTarget() const { return target; }
private:
	PlayerParameter param;				// パラメーター
	std::weak_ptr<Camera> camera;
	std::weak_ptr<Enemy> target;

	void SearchTarget();
	VECTOR GetInputDir()const;
};
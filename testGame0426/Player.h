#pragma once
#include "DamageableObject.h"
#include "PlayerParameter.h"
#include "AttackData.h"

class Camera;
class PlayerStateBase;
class AttackHitSphere;
class Player :	public DamageableObject
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
private:
	PlayerParameter param;				// パラメーター
	std::weak_ptr<Camera> camera;
	AttackData attackData;
};
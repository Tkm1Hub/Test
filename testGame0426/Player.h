#pragma once
#include "CharacterBase.h"
#include "PlayerParameter.h"
#include "AttackData.h"

enum class PlayerAnimState :int
{
	None = -1,			// なし
	Idle = 0,			// アイドル
	Walk = 1,			// 歩き
};

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

	void Fire(const AttackStep& step);		// 射撃

	void OnHit(const DamageInfo& info) override;

	const AttackData& GetAttackData() { return attackData; }
	const AttackStep& GetFireData() { return fireData; }

	PlayerParameter& GetParam() { return param; }

	float GetAttackMoveSpeed(const AttackStep& step);
	VECTOR GetAttackDirection();
	VECTOR GetInputDir()const;

	std::weak_ptr<Enemy> GetTarget() const { return target; }
	bool GetIsLockOn()const { return isLockOn; }
	void SetIsLockOn(bool flag) { isLockOn = flag; }

	bool GetIsAim() const { return isAim; }
	void SetIsAim(bool flag) { isAim = flag; }
private:
	PlayerParameter param;				// パラメーター
	AttackStep fireData;				// 射撃データ
	std::weak_ptr<Camera> camera;
	std::weak_ptr<Enemy> target;

	bool isLockOn = false;
	bool isAim = false;
	bool canSwitchTarget = false;

	int currentBulletNum = 0;
	void SearchTarget();
	void ToggleLockOn();
};
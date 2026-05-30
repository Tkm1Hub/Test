#pragma once
#include "CharacterBase.h"
#include "PlayerParameter.h"
#include "AttackData.h"

enum class PlayerAnimState :int
{
	None = -1,			// なし
	Idle = 0,			// アイドル
	Walk = 1,			// 歩き
	JumpUp = 2,			// ジャンプ開始
	Fall = 3,			// 落下
	Aim = 4,				// エイム
	AimWalkFront = 5,	// エイム移動
	AimWalkLeft = 6,		// エイム移動
	AimWalkRight = 7,	// エイム移動
	AimWalkBack = 8,		// エイム移動
	Fire = 9,			// 発射
	Dive = 10,			// 回避
	DodgeBack = 11,		// 後ろ回避
	Slash1 = 12,			// 攻撃1
	Slash2 = 13,			// 攻撃1
	Slash3 = 14,			// 攻撃1
	Slash4 = 15,			// 攻撃1
	Slash5 = 16,			// 攻撃1
	BlockStart = 17,		// ガード開始
	BlockIdle = 18,		// ガード中
	Parry = 19,			// パリィ
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

	void AddBullet();
	int GetCurrentBulletNum()const { return currentBulletNum; }
	void ConsumeBullet();

	bool CanParry() const;
	void OnParry(const DamageInfo& info);
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
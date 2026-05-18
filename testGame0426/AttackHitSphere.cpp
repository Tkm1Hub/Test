#include "stdafx.h"
#include "AttackHitSphere.h"
#include "AttackCollision.h"
#include "CharacterBase.h"
#include "Time.h"

void AttackHitSphere::InitMelee(
	int damage,
	float stunPower,
	float radius,
	float offset,
	float knockBackPower,
	CharacterBase* owner,
	const VECTOR& attackDir
)
{
	isFollowOwner = true;

	this->radius = radius;
	this->forwardOffset = offset;
	this->owner = owner;

	lifeTime = 0.1f;

	damageInfo.damage = damage;
	damageInfo.stunPower = stunPower;
	damageInfo.knockBackPower = knockBackPower;
	damageInfo.attacker = owner;
	damageInfo.hitDir = VNorm(attackDir);

	pos = VAdd(
		owner->GetCapsuleCenter(),
		VScale(
			damageInfo.hitDir,
			forwardOffset
		)
	);
}

void AttackHitSphere::InitProjectile(
	const VECTOR& startPos,
	float radius,
	int damage,
	float stunPower,
	float knockBackPower,
	CharacterBase* owner,
	const VECTOR& dir,
	float speed
)
{
	isFollowOwner = false;

	pos = startPos;

	this->radius = radius;
	this->owner = owner;

	lifeTime = 5.0f;

	velocity =
		VScale(
			VNorm(dir),
			speed
		);

	damageInfo.damage = damage;
	damageInfo.stunPower = stunPower;
	damageInfo.attacker = owner;
	damageInfo.hitDir = VNorm(dir);
	damageInfo.knockBackPower =
		knockBackPower;
}

void AttackHitSphere::Update()
{
	timer +=
		Time::GetInstance().GetDeltaTime();

	if (timer >= lifeTime)
	{
		isDestroy = true;
	}

	// ‹ßÚ
	if (isFollowOwner)
	{
		pos = VAdd(
			owner->GetCapsuleCenter(),
			VScale(
				damageInfo.hitDir,
				forwardOffset
			)
		);
	}
	// ”ò‚Ñ“¹‹ï
	else
	{
		pos = VAdd(
			pos,
			VScale(
				velocity,
				Time::GetInstance().GetDeltaTime() * 60.0f
			)
		);
	}

	AttackCollision::ProcessHit(this);
}

void AttackHitSphere::Draw()
{
	DrawSphere3D(
		pos,
		radius,
		16,
		GetColor(255, 0, 0),
		GetColor(255, 255, 255),
		FALSE
	);
}

bool AttackHitSphere::HasHitObject(Object* obj) const
{
	return hitObjects.contains(obj);
}

void AttackHitSphere::AddHitObject(Object* obj)
{
	hitObjects.insert(obj);
}
#pragma once
#include "Object.h"
#include <unordered_set>
#include "DamageInfo.h"

class CharacterBase;
class AttackHitSphere :public Object
{
public:
	void InitMelee(
		float offset,
		float radius,
		int damage,
		CharacterBase* owner,
		const VECTOR& attackDir
	);

	void InitProjectile(
		const VECTOR& startPos,
		float radius,
		int damage,
		CharacterBase* owner,
		const VECTOR& dir,
		float speed
	);

	void Update() override;
	void Draw() override;

	float GetRadius() const { return radius; }
	CharacterBase* GetOwner() const { return owner; }

	bool HasHitObject(Object* obj) const;
	void AddHitObject(Object* obj);
	const DamageInfo& GetDamageInfo() const { return damageInfo; }

private:
	float radius = 0.0f;
	int damage = 0;
	float lifeTime = 0.0f;
	float timer = 0.0f;

	float forwardOffset = 0.0f;

	bool isFollowOwner = true;

	VECTOR velocity = VGet(0.0f, 0.0f, 0.0f);

	CharacterBase* owner = nullptr;
	std::unordered_set<Object*> hitObjects;
	DamageInfo damageInfo;
};
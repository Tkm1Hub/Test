#pragma once
#include "Object.h"
#include <unordered_set>
#include "DamageInfo.h"

class AttackHitSphere :public Object
{
public:
	void Init(
		float offset,
		float radius,
		int damage,
		Object* owner
	);

	void Update() override;
	void Draw() override;

	float GetRadius() const { return radius; }
	Object* GetOwner() const { return owner; }

	bool HasHitObject(Object* obj) const;
	void AddHitObject(Object* obj);
	const DamageInfo& GetDamageInfo() const { return damageInfo; }

private:
	float radius = 0.0f;
	int damage = 0;
	float lifeTime = 0.1f;
	float timer = 0.0f;

	float forwardOffset = 0.0f;

	Object* owner = nullptr;
	std::unordered_set<Object*> hitObjects;
	DamageInfo damageInfo;
};
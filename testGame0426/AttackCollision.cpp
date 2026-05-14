#include "stdafx.h"
#include "AttackCollision.h"
#include "AttackHitSphere.h"
#include "DamageableObject.h"
#include "Objects.h"

bool AttackCollision::CheckHit(
	AttackHitSphere* hitSphere,
	Object* target
)
{
	VECTOR capsuleBottom = target->GetCapsuleBottom();
	VECTOR capsuleTop = target->GetCapsuleTop();

	VECTOR line = VSub(capsuleTop, capsuleBottom);

	VECTOR toSphere = 
		VSub(hitSphere->GetPosition(),capsuleBottom);

	float lineLengthSq = VDot(line, line);

	float t = 0.0f;

	if (lineLengthSq > 0.0f)
	{
		t = VDot(toSphere, line) / lineLengthSq;
		t = std::clamp(t, 0.0f, 1.0f);
	}

	VECTOR closetPoint =
		VAdd(capsuleBottom, VScale(line, t));

	float distance =
		VSize(
			VSub(
				hitSphere->GetPosition(),
				closetPoint
			)
		);

	return distance <=
		(
			hitSphere->GetRadius() +
			target->GetBodyRadius()
			);
}

void AttackCollision::ProcessHit(AttackHitSphere* hitSphere)
{
	for (auto& obj : Objects::GetInstance().objects)
	{
		// ownerは無視
		if (obj.get() == hitSphere->GetOwner())
			continue;

		// 無効オブジェクト無視
		if (!obj->GetIsActive())
			continue;

		// 当たり判定off無視
		if ((!obj->GetIsCollision()))
			continue;

		// 既にHit済み無視
		if (hitSphere->HasHitObject(obj.get()))
			continue;

		// 当たり判定
		if (CheckHit(hitSphere, obj.get()))
		{
			// Hit記録
			hitSphere->AddHitObject(obj.get());

			// 被弾通知
			obj->OnHit(hitSphere->GetDamageInfo());
		}
	}
}
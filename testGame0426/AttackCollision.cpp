#include "stdafx.h"
#include "AttackCollision.h"
#include "AttackHitSphere.h"
#include "DamageableObject.h"
#include "CharacterBase.h"
#include "Objects.h"
#include "Time.h"

bool AttackCollision::CheckHit(
	AttackHitSphere* hitSphere,
	CharacterBase* target
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
	auto owner = hitSphere->GetOwner();

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

		// CharacterBaseか確認
		auto character =
			dynamic_cast<CharacterBase*>(obj.get());
		if (!character)
			continue;

		// 同チーム無視
		if (owner->GetTeam() ==
			character->GetTeam())
		{
			continue;
		}

		// 既にHit済み無視
		if (hitSphere->HasHitObject(obj.get()))
			continue;


		// 当たり判定
		if (CheckHit(hitSphere, character))
		{
			// Hit記録
			hitSphere->AddHitObject(obj.get());

			// プレイヤーの攻撃のみヒットストップ
			if (hitSphere->GetOwner()->GetTeam() == Team::Player)
			{
				Time::GetInstance().StartHitStop(0.05f);
			}

			// 被弾通知
			character->OnHit(hitSphere->GetDamageInfo());
		}
	}
}
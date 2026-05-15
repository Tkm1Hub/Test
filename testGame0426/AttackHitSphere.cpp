#include "stdafx.h"
#include "AttackHitSphere.h"
#include "AttackCollision.h"
#include "CharacterBase.h"
#include "Time.h"

void AttackHitSphere::Init(
    float offset,
    float radius,
    int damage,
    CharacterBase* owner
)
{
    forwardOffset = offset;
    this->radius = radius;
    this->damage = damage;
    this->owner = owner;

    // ダメージ情報
    damageInfo.damage = damage;
    damageInfo.attacker = owner;
    damageInfo.hitDir = owner->GetForward();
    damageInfo.knockBackPower = 15.0f;

    pos = VAdd(
        owner->GetCapsuleCenter(),
        VScale(owner->GetForward(), forwardOffset)
    );
}

void AttackHitSphere::Update()
{
    timer +=
        Time::GetInstance().GetDeltaTime();

    if (timer >= lifeTime)
    {
        isDestroy = true;
    }

    // owner前方へ配置
    pos = VAdd(
        owner->GetCapsuleCenter(),
        VScale(owner->GetForward(), forwardOffset)
    );

    // 攻撃判定
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

bool AttackHitSphere::HasHitObject(Object* obj)const
{
    return hitObjects.contains(obj);
}

void AttackHitSphere::AddHitObject(Object* obj)
{
    hitObjects.insert(obj);
}
#include "stdafx.h"
#include "AttackHitSphere.h"
#include "AttackCollision.h"
#include "CharacterBase.h"
#include "Time.h"

void AttackHitSphere::InitMelee(
    float offset,
    float radius,
    int damage,
    CharacterBase* owner,
    const VECTOR& attackDir
)
{
    isFollowOwner = true;

    forwardOffset = offset;
    this->radius = radius;
    this->damage = damage;
    this->owner = owner;

    lifeTime = 0.1f;

    // É_ÉÅÅ[ÉWèÓïÒ
    damageInfo.damage = damage;
    damageInfo.attacker = owner;
    damageInfo.hitDir = VNorm(attackDir);
    damageInfo.knockBackPower = 15.0f;

    pos = VAdd(
        owner->GetCapsuleCenter(),
        VScale(owner->GetForward(), forwardOffset)
    );
}

void AttackHitSphere::InitProjectile(
    const VECTOR& startPos,
    float radius,
    int damage,
    CharacterBase* owner,
    const VECTOR& dir,
    float speed
)
{
    isFollowOwner = false;

    pos = startPos;
    this->radius = radius;
    this->damage = damage;
    this->owner = owner;

    lifeTime = 5.0f;

    velocity =
        VScale(
            VNorm(dir),
            speed
        );

    damageInfo.damage = damage;
    damageInfo.attacker = owner;
    damageInfo.hitDir = VNorm(dir);
    damageInfo.knockBackPower = 15.0f;
}

void AttackHitSphere::Update()
{
    timer +=
        Time::GetInstance().GetDeltaTime();

    if (timer >= lifeTime)
    {
        isDestroy = true;
    }

    // ãﬂê⁄
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
    // îÚÇ—ìπãÔ
    else
    {
        pos = VAdd(
            pos,
            VScale(
                velocity,
                Time::GetInstance().GetDeltaTime() * 60.0f
            ));
    }

    // çUåÇîªíË
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
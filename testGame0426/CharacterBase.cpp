#include "stdafx.h"
#include "CharacterBase.h"
#include "StageCollision.h"

void CharacterBase::ResolveStageCollision()
{
    auto result =
        StageCollision::GetInstance().CheckCollision(
            *this,
            pos
        );

    pos = result.position;

    // 天井ヒット
    if (result.hitRoof)
    {
        verticalVelocity = 0.0f;
    }

    // 着地判定
    if (result.isGround)
    {
        isGround = true;

        if (verticalVelocity < 0.0f)
        {
            verticalVelocity = 0.0f;
        }
    }
    else
    {
        if (wasGround)
        {
            verticalVelocity += FallUpPower;
        }

        isGround = false;
    }

    wasGround = isGround;
}

VECTOR CharacterBase::GetCapsuleBottom()const
{
    return VAdd(pos, VGet(0, bodyRadius, 0));
}

VECTOR CharacterBase::GetCapsuleTop()const
{
    return VAdd(GetCapsuleBottom(), VGet(0.0f, bodyHeight, 0.0f));
}

VECTOR CharacterBase::GetCapsuleCenter()const
{
    return VAdd(
        pos,
        VGet(
            0.0f,
            bodyRadius + bodyHeight * 0.5f,
            0.0f
        )
    );
}

void CharacterBase::SetupCombo(
    const std::vector<AttackStep>& comboData
)
{
    attackData.combo = comboData;
}


#include "stdafx.h"
#include "CharacterBase.h"

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
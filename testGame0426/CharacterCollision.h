#pragma once

class CharacterBase;

class CharacterCollision
{
public:
    static void Resolve();

private:
    static bool ResolveCapsuleCollision(
        CharacterBase* a,
        CharacterBase* b
    );

    static float DistanceSegmentToSegment(
        VECTOR p1,
        VECTOR q1,
        VECTOR p2,
        VECTOR q2
    );

    static VECTOR ClosestPointOnSegment(
        const VECTOR& a,
        const VECTOR& b,
        const VECTOR& p
    );
};
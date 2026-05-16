#include "stdafx.h"
#include "CharacterCollision.h"
#include "CharacterBase.h"
#include "Objects.h"

void CharacterCollision::Resolve()
{
    auto& objects =
        Objects::GetInstance().objects;

    for (size_t i = 0; i < objects.size(); i++)
    {
        auto a =
            dynamic_cast<CharacterBase*>(
                objects[i].get()
                );

        if (!a)
            continue;

        for (size_t j = i + 1;
            j < objects.size();
            j++)
        {
            auto b =
                dynamic_cast<CharacterBase*>(
                    objects[j].get()
                    );

            if (!b)
                continue;

            ResolveCapsuleCollision(a, b);
        }
    }
}

// カプセル同士の衝突をチェックして押し戻す
bool CharacterCollision::
ResolveCapsuleCollision(
    CharacterBase* a,
    CharacterBase* b)
{
    float radiusA = a->GetBodyRadius();
    float radiusB = b->GetBodyRadius();

    VECTOR topA = a->GetCapsuleTop();
    VECTOR bottomA = a->GetCapsuleBottom();

    VECTOR topB = b->GetCapsuleTop();
    VECTOR bottomB = b->GetCapsuleBottom();

    // --- カプセル B の軸に対する、カプセル A の最近接点 ---
    VECTOR closestA = ClosestPointOnSegment(bottomA, topA, bottomB);  // A軸上のB下端に最も近い点
    VECTOR closestB = ClosestPointOnSegment(bottomB, topB, bottomA);  // B軸上のA下端に最も近い点

    // A軸の最近接点 ＝ Bカプセルの最近接点
    // B軸の最近接点 ＝ Aカプセルの最近接点
    // → ２つの最も近い点同士で判定すればOK
    VECTOR diff = VSub(closestB, closestA);

    // Y方向は無視
    diff.y = 0.0f;

    float dist = VSize(diff);
    float minDist = radiusA + radiusB;

    // 衝突してない
    if (dist >= minDist)
        return false;

    // ゼロ距離対策
    if (dist <= 0.0001f)
        return false;


    float penetration = minDist - dist;

    VECTOR pushDir = VNorm(diff);

    // 半分ずつ押し戻し
    VECTOR pushA = VScale(pushDir, -penetration * 0.5f);
    VECTOR pushB = VScale(pushDir, penetration * 0.5f);

    a->SetPosition(VAdd(a->GetPosition(), pushA));
    b->SetPosition(VAdd(b->GetPosition(), pushB));

    return true;
}


// カプセル同士の最短距離を求める
float CharacterCollision::DistanceSegmentToSegment(VECTOR p1, VECTOR q1, VECTOR p2, VECTOR q2)
{
    VECTOR d1 = VSub(q1, p1);  // 線分1
    VECTOR d2 = VSub(q2, p2);  // 線分2
    VECTOR r = VSub(p1, p2);

    float a = VDot(d1, d1);  // 長さの2乗
    float e = VDot(d2, d2);
    float f = VDot(d2, r);

    float s, t;

    if (a <= 0.0001f && e <= 0.0001f)
    {
        return VSize(r); // 両方とも点
    }

    if (a <= 0.0001f)
    {
        s = 0.0f;
        t = f / e;
        t = (t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t));
    }
    else
    {
        float c = VDot(d1, r);
        if (e <= 0.0001f)
        {
            t = 0.0f;
            s = -c / a;
            s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
        }
        else
        {
            float b = VDot(d1, d2);
            float denom = a * e - b * b;

            if (denom != 0.0f)
            {
                s = (b * f - c * e) / denom;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
            else
            {
                s = 0.0f;
            }

            t = (b * s + f) / e;

            if (t < 0.0f)
            {
                t = 0.0f;
                s = (-c) / a;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
            else if (t > 1.0f)
            {
                t = 1.0f;
                s = (b - c) / a;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
        }
    }

    VECTOR c1 = VAdd(p1, VScale(d1, s));
    VECTOR c2 = VAdd(p2, VScale(d2, t));

    return VSize(VSub(c1, c2));
}

// 点p に対して、線分 ab 上の最近接点を求める
VECTOR CharacterCollision::ClosestPointOnSegment(const VECTOR& a, const VECTOR& b, const VECTOR& p)
{
    VECTOR ab = VSub(b, a);
    VECTOR ap = VSub(p, a);

    float abLenSq = VDot(ab, ab);
    if (abLenSq <= 0.00001f) return a; // 長さ0対策

    float t = VDot(ap, ab) / abLenSq;

    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    return VAdd(a, VScale(ab, t));
}
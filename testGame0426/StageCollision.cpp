#include "stdafx.h"
#include "StageCollision.h"

void StageCollision::SetStageCollision(const int collisionModelHandle)
{
    modelHandle = collisionModelHandle;
}

/// <summary>
/// 当たり判定をして、補正した移動先のポジションを返す
/// </summary>
StageCollisionResult StageCollision::CheckCollision(CharacterBase& object, const VECTOR& nextPos)
{
    StageCollisionResult result;

    VECTOR oldPos = object.GetPosition();       // 移動前の座標
    VECTOR newPos = nextPos;

    // プレイヤーの周囲にあるステージポリゴンを取得する
    // ( 検出する範囲は移動距離も考慮する )
    auto hitDim = MV1CollCheck_Sphere(modelHandle, -1, oldPos, DefaultSize + VSize(newPos));

    // 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
    AnalyzeWallAndFloor(hitDim, oldPos);

    // 壁ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    newPos = CheckHitWithWall(object, newPos);

    result.position = newPos;

    // 床ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    CheckHitWithFloor(object, result);

    // 検出したプレイヤーの周囲のポリゴン情報を開放する
    MV1CollResultPolyDimTerminate(hitDim);

    return result;
}

/// <summary>
/// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
/// </summary>
void StageCollision::AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition)
{
    // 壁ポリゴンと床ポリゴンの数を初期化する
    wallNum = 0;
    floorNum = 0;

    // 検出されたポリゴンの数だけ繰り返し
    for (int i = 0; i < hitDim.HitNum; i++)
    {
        const auto& poly = hitDim.Dim[i];
        // ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
        if (poly.Normal.y < 0.000001f && poly.Normal.y > -0.000001f)
        {
            if ((poly.Position[0].y > checkPosition.y + 1.0f ||
                poly.Position[1].y > checkPosition.y + 1.0f ||
                poly.Position[2].y > checkPosition.y + 1.0f) && wallNum < MaxHitColl)
            {
                wall[wallNum++] = &hitDim.Dim[i];
            }
        }
        else
        {
            if (floorNum < MaxHitColl)
            {
                floor[floorNum++] = &hitDim.Dim[i];
            }
        }
    }
}

/// <summary>
/// 壁ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
/// </summary>
VECTOR StageCollision::CheckHitWithWall(CharacterBase& object, const VECTOR& checkPosition)
{
    VECTOR fixedPos = checkPosition;

    float HitRadius = object.GetBodyRadius();
    float HitHeight = object.GetBodyHeight();

    // 壁の数が無かったら早期リターン
    if (wallNum == 0)
        return fixedPos;

    // 壁からの押し出し処理を試みる最大数だけ繰り返し
    for (int k = 0; k < HitTryNum; k++)
    {
        // 当たる可能性のある壁ポリゴンを全て見る
        bool isHitWall = false;
        for (int i = 0; i < wallNum; i++)
        {
            // i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
            auto poly = wall[i];

            // プレイヤーと当たっているなら
            if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)), HitRadius,
                poly->Position[0], poly->Position[1], poly->Position[2]))
            {
                // 規定距離分プレイヤーを壁の法線方向に移動させる
                // 移動後の位置を更新（移動後の場所を補正）
                fixedPos = VAdd(fixedPos, VScale(poly->Normal, HitSlideLength));

                // 移動した壁ポリゴンと接触しているかどうかを判定
                for (int j = 0; j < wallNum; j++)
                {
                    // 当たっていたらループを抜ける
                    auto checkPoly = wall[j];
                    if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)), HitRadius,
                        checkPoly->Position[0], checkPoly->Position[1], checkPoly->Position[2]))
                    {
                        isHitWall = true;
                        break;
                    }
                }

                // 全てのポリゴンと当たっていなかったらここでループ終了
                if (!isHitWall) break;
            }
        }

        // 全部のポリゴンで押し出しを試みる前に
        // 全ての壁ポリゴンと接触しなくなったらループから抜ける
        if (!isHitWall)
            break;
    }

    return fixedPos;
}

/// <summary>
/// 床ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
/// </summary>
void StageCollision::CheckHitWithFloor(CharacterBase& object, StageCollisionResult& result)
{
    VECTOR fixedPos = result.position;
    const float hitHeight = object.GetBodyHeight();

    constexpr float kUpwardThreshold = 0.01f;

    result.hitRoof = false;
    result.isGround = false;

    // 床ポリゴンが無ければ空中扱い
    if (floorNum == 0)
    {
        result.position = fixedPos;
        return;
    }

    const float verticalVelocity = object.GetVerticalVelocity();

    //========================
    // 上昇中：天井判定
    //========================
    if (verticalVelocity > kUpwardThreshold)
    {
        bool isHitRoof = false;
        float minY = 0.0f;

        for (int i = 0; i < floorNum; i++)
        {
            auto poly = floor[i];

            HITRESULT_LINE lineResult =
                HitCheck_Line_Triangle(
                    fixedPos,
                    VAdd(fixedPos, VGet(0.0f, hitHeight, 0.0f)),
                    poly->Position[0],
                    poly->Position[1],
                    poly->Position[2]
                );

            if (!lineResult.HitFlag)
            {
                continue;
            }

            if (!isHitRoof || lineResult.Position.y < minY)
            {
                isHitRoof = true;
                minY = lineResult.Position.y;
            }
        }

        if (isHitRoof)
        {
            fixedPos.y = minY - hitHeight;
            result.hitRoof = true;
        }
    }
    //========================
    // 下降中・地上移動中：床判定
    //========================
    else
    {
        bool isHitFloor = false;
        float maxY = 0.0f;

        for (int i = 0; i < floorNum; i++)
        {
            auto poly = floor[i];

            HITRESULT_LINE lineResult =
                HitCheck_Line_Triangle(
                    VAdd(fixedPos, VGet(0.0f, hitHeight, 0.0f)),
                    VAdd(fixedPos, VGet(0.0f, -0.5f, 0.0f)),
                    poly->Position[0],
                    poly->Position[1],
                    poly->Position[2]
                );

            if (!lineResult.HitFlag)
            {
                continue;
            }

            if (!isHitFloor || lineResult.Position.y > maxY)
            {
                isHitFloor = true;
                maxY = lineResult.Position.y;
            }
        }

        if (isHitFloor)
        {
            fixedPos.y = maxY;
            result.isGround = true;
        }
    }

    result.position = fixedPos;
}
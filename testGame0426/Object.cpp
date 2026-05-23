#include "Object.h"
#include "Time.h"

void Object::Draw()
{
    // 向いてる方向表示
    DrawLine3D(
        VAdd(pos, VGet(0.0f, 2.5f, 0.0f)),
        VAdd(
            VAdd(pos, VGet(0.0f, 2.5f, 0.0f)),
            VScale(forward, 50.0f)
        ),
        GetColor(255, 0, 0)
    );

    // 入力方向表示
    DrawLine3D(
        VAdd(pos, VGet(0.0f, 2.0f, 0.0f)),
        VAdd(
            VAdd(pos, VGet(0.0f, 2.0f, 0.0f)),
            VScale(moveDir, 40.0f)
        ),
        GetColor(0, 255, 0)
    );

    // Velocity
    DrawLine3D(
        pos,
        VAdd(pos, VScale(moveVelocity, 30.0f)),
        GetColor(0, 0, 255)
    );
}

void Object::AddVerticalVelocity(float power)
{
    verticalVelocity = power;

    if (verticalVelocity > 0.0f)
    {
        isGround = false;
    }
}

void Object::ApplyGravity()
{
    // 着地状態だと早期リターン
    if (isGround)return;

	verticalVelocity -= gravity;
	
	// 速度が早くなりすぎないように制限
	if (verticalVelocity < -5.0)
	{
		verticalVelocity = -5.0;
	}

}

void Object::ApplyVelocity()
{
    // 上方向に向いているなら空中
    if (verticalVelocity > 0.0f)
    {
        isGround = false;
    }

    isMove = (VSize(moveDir) > 0.01f);

    CalcMoveSpeed();

    float dt =
        Time::GetInstance().GetScaledDeltaTime()
        * 60.0f;

    moveVelocity.y = verticalVelocity;

    VECTOR finalVelocity =VAdd(moveVelocity, externalVelocity);

    pos = VAdd(pos, VScale(finalVelocity, dt));

    if (pos.y < 0.0f)
    {
        pos.y = 0.0f;
        verticalVelocity = 0.0f;
        isGround = true;
    }
}

void Object::CalcMoveSpeed()
{
    float dt =
        Time::GetInstance().GetScaledDeltaTime()
        * 60.0f;

    if (isMove)
    {
        VECTOR targetVelocity =
            VScale(moveDir, maxMoveSpeed);

        moveVelocity = VAdd(
            moveVelocity,
            VScale(
                VSub(targetVelocity, moveVelocity),
                moveAccel * dt
            )
        );
    }
    else
    {
        float decel = powf(moveDecel, dt);

        moveVelocity.x *= decel;
        moveVelocity.z *= decel;

        if (fabs(moveVelocity.x) < 0.001f)
            moveVelocity.x = 0.0f;

        if (fabs(moveVelocity.z) < 0.001f)
            moveVelocity.z = 0.0f;
    }

    float decel = powf(extDecel, dt);

    externalVelocity.x *= decel;
    externalVelocity.z *= decel;

    if (fabs(externalVelocity.x) < 0.001f)
        externalVelocity.x = 0.0f;

    if (fabs(externalVelocity.z) < 0.001f)
        externalVelocity.z = 0.0f;


    float speed = sqrtf(
            moveVelocity.x * moveVelocity.x +
            moveVelocity.z * moveVelocity.z
        );

    if (speed > maxMoveSpeed)
    {
        float rate = maxMoveSpeed / speed;

        moveVelocity.x *= rate;
        moveVelocity.z *= rate;
    }
}

void Object::RotateAngle()
{
    if (VSize(lookDir) <= 0.01f) return;

    forward = VNorm(
        VAdd(
            VScale(forward, 1.0f - angleSpeed),
            VScale(lookDir, angleSpeed)
        )
    );
}
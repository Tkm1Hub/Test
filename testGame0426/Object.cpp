#include "Object.h"
#include "Time.h"

void Object::Draw()
{
    MV1SetOpacityRate(
        modelHandle,
        alpha
    );

    MV1DrawModel(modelHandle);
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
    float dt =
        Time::GetInstance().GetScaledDeltaTime()
        * 60.0f;

    // 着地状態だと早期リターン
    if (isGround)return;

	verticalVelocity -= gravity * dt;
	
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

    if (pos.y < -50.0f)
    {
        pos = VGet(0.0f,0.0f,0.0f);
        verticalVelocity = 0.0f;
        isGround = true;
    }

    MV1SetPosition(modelHandle, pos);
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

    forward =
        VAdd(
            VScale(forward, 1.0f - angleSpeed),
            VScale(lookDir, angleSpeed)
        );

    forward.y = 0;

    forward = VNorm(forward);

    // forward から Y回転角度を作る
    float rotY = atan2f(forward.x, forward.z);

    rotY += DX_PI_F;

    MV1SetRotationXYZ(
        modelHandle,
        VGet(0.0f, rotY, 0.0f)
    );
}

void Object::StartFadeIn()
{
    alpha = 0.0f;
    isFadeIn = true;
    isFadeOut = false;
}

void Object::StartFadeOut()
{
    isFadeOut = true;
    isFadeIn = false;
}

void Object::UpdateFade()
{
    if (isFadeIn)
    {
        alpha += fadeSpeed;

        if (alpha >= 1.0f)
        {
            alpha = 1.0f;
            isFadeIn = false;
        }
    }

    if (isFadeOut)
    {
        alpha -= fadeSpeed;

        if (alpha <= 0.0f)
        {
            alpha = 0.0f;
            isFadeOut = false;

        }
    }
}
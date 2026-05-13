#include "Object.h"
#include "Time.h"

void Object::Draw()
{
    // å¸Ç¢ÇƒÇÈï˚å¸ï\é¶
    DrawLine3D(
        VAdd(pos, VGet(0.0f, 2.5f, 0.0f)),
        VAdd(
            VAdd(pos, VGet(0.0f, 2.5f, 0.0f)),
            VScale(forward, 10.0f)
        ),
        GetColor(255, 0, 0)
    );

    // ì¸óÕï˚å¸ï\é¶
    DrawLine3D(
        VAdd(pos, VGet(0.0f, 2.0f, 0.0f)),
        VAdd(
            VAdd(pos, VGet(0.0f, 2.0f, 0.0f)),
            VScale(moveDir, 8.0f)
        ),
        GetColor(0, 255, 0)
    );

    // Velocity
    DrawLine3D(
        pos,
        VAdd(pos, VScale(moveVelocity, 8.0f)),
        GetColor(0, 0, 255)
    );
}

void Object::ApplyGravity()
{
	if (isGround) return;

	verticalVelocity -= gravity;
	
	// ë¨ìxÇ™ëÅÇ≠Ç»ÇËÇ∑Ç¨Ç»Ç¢ÇÊÇ§Ç…êßå¿
	if (verticalVelocity < -1.0f)
	{
		verticalVelocity = -1.0;
	}

}

void Object::ApplyVelocity()
{
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
        moveVelocity.x += forward.x * moveAccel * dt;
        moveVelocity.z += forward.z * moveAccel * dt;
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

    float decel = powf(moveDecel, dt);
    float extDecel = powf(decel, dt);

    externalVelocity.x *= extDecel;
    externalVelocity.z *= extDecel;

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
    if (VSize(moveDir) <= 0.01f) return;

    forward = VNorm(
        VAdd(
            VScale(forward, 1.0f - angleSpeed),
            VScale(moveDir, angleSpeed)
        )
    );
}
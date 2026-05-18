#include "stdafx.h"
#include "Input.h"

void Input::Update()
{
    // 前フレーム保存
    oldState = nowState;

    // XInput取得
    GetJoypadXInputState(DX_INPUT_KEY_PAD1,&nowState);

    UpdateStick();
}

bool Input::IsPress(int button) const
{
    return nowState.Buttons[button] == 1;
}

bool Input::IsTrigger(int button) const
{
    return
        nowState.Buttons[button] == 1 &&
        oldState.Buttons[button] == 0;
}

VECTOR Input::GetLeftStickDir() const
{
    return VNorm(
        VGet(
        leftStickX,
        0.0f,
        -leftStickY
    ));
}

/// @brief スティックの数値を計算
void Input::CalcStickInput()
{
    int inputX_L = 0;
    int inputY_L = 0;
    int inputX_R = 0;
    int inputY_R = 0;

    leftStickX = 0.0f;
    leftStickY = 0.0f;
    rightStickX = 0.0f;
    rightStickY = 0.0f;

    // 左右のスティックの状態を取得
    GetJoypadAnalogInput(&inputX_L, &inputY_L, DX_INPUT_PAD1);
    GetJoypadAnalogInputRight(&inputX_R, &inputY_R, DX_INPUT_PAD1);

    // デッドゾーン以上の場合floatに変換して保存
    // 左スティック
    if (fabs(inputX_L) > DEADZONE || fabs(inputY_L) > DEADZONE)
    {
        isMoveLStick = true;

        leftStickX = static_cast<float>(inputX_L);
        leftStickY = static_cast<float>(inputY_L);
    }
    else
    {
        isMoveLStick = false;
    }

    // 右スティック
    if (fabs(inputX_R) > DEADZONE || fabs(inputY_R) > DEADZONE)
    {
        isMoveRStick = true;

        rightStickX = static_cast<float>(inputX_R);
        rightStickY = static_cast<float>(inputY_R);
    }
    else
    {
        isMoveRStick = false;
    }

    //スティックの傾き度合いを計算
    rightStickPower = fabs(sqrtf(rightStickX * rightStickX + rightStickY * rightStickY));
    leftStickPower = fabs(sqrtf(leftStickX * leftStickX + leftStickY * leftStickY));
    // 1000を上限にクランプ（超えたら1000にする）
    if (rightStickPower > 1000.0f) rightStickPower = 1000.0f;
    if (leftStickPower > 1000.0f) leftStickPower = 1000.0f;
}

void Input::UpdateStick()
{
    // -1.0 ～ 1.0
    leftStickX = nowState.ThumbLX / 32767.0f;

    leftStickY = nowState.ThumbLY / 32767.0f;

    rightStickX = nowState.ThumbRX / 32767.0f;

    rightStickY = nowState.ThumbRY / 32767.0f;

    // デッドゾーン
    isMoveLStick = (fabs(leftStickX) > DEADZONE || fabs(leftStickY) > DEADZONE);

    isMoveRStick = (fabs(rightStickX) > DEADZONE || fabs(rightStickY) > DEADZONE);

    // デッドゾーン内は0
    if (!isMoveLStick)
    {
        leftStickX = 0.0f;
        leftStickY = 0.0f;
    }

    if (!isMoveRStick)
    {
        rightStickX = 0.0f;
        rightStickY = 0.0f;
    }

    // トリガー
    leftTrigger = nowState.LeftTrigger / 255.0f;

    rightTrigger = nowState.RightTrigger / 255.0f;
}
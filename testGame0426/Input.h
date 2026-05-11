#pragma once
#pragma once

//一人プレイのみのためシングルトンで作成
class Input
{
private:
    //コンストラクタを非公開にする
    Input() {}

    // コピーコンストラクタと代入演算子を削除
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    //プライベートデストラクタ
    ~Input() {}

public:
    // インスタンスを取得するためのメソッド
    static Input& GetInput()
    {
        static Input instance;      // 静的変数としてインスタンスを定義
        return instance;
    }

    XINPUT_STATE inputState;

    //キーの種類
    enum KeyKinds
    {
        Move = 0,  //移動キーのどれか
        Left = 1,  //右
        Right = 2,  //左
        Up = 3,  //上
        Down = 4,  //下
        Space = 5,  //スペース
        LB = 6,  //左上の手前のボタン
        LT = 7,  //左上の奥側のボタン
        RB = 8,  //右上の手前のボタン
        RT = 9,  //右奥側のボタン
        X = 10,
        Y = 11,
        A = 12,
        B = 13,
        LeftStick = 14,  //左スティック押し込み
        None = 15,  //使用しないキーもしくは押されていない
    };

    void Update();

    int GetNowFrameInput() const { return nowFrameInput; }
    int GetNowFrameNewInput() const { return nowFrameNewInput; }

    bool GetIsMoveLStick() const { return isMoveLStick; }
    bool GetIsMoveRStick() const { return isMoveRStick; }

    float GetLeftStickX() const { return leftStickX; }
    float GetLeftStickY() const { return leftStickY; }
    float GetRightStickX() const { return rightStickX; }
    float GetRightStickY() const { return rightStickY; }

    float GetRightStickPower() const { return rightStickPower; }
    float GetLeftStickPower() const { return leftStickPower; }
private:
    static constexpr int DEADZONE = 10;     // スティックを倒してもすぐ反応しない領域

    int nowFrameInput = 0;          // 現在のフレームで押されているボタン
    int nowFrameNewInput = 0;       // 現在のフレームで新たに押されたボタン
    bool isMoveRStick = false;      // 右スティックが傾いているか
    bool isMoveLStick = false;      // 左スティックが傾いているか

    float leftStickX = 0.0f;        // 左スティックのX軸の傾き
    float leftStickY = 0.0f;        // 左スティックのY軸の傾き
    float rightStickX = 0.0f;       // 右スティックのX軸の傾き
    float rightStickY = 0.0f;       // 右スティックのY軸の傾き
    float leftStickPower = 0.0f;       // 左スティックの傾き度
    float rightStickPower = 0.0f;       // 右スティックの傾き度

    void CalcStickInput();

};
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

    void Update();

    // ボタン取得
    bool IsPress(int button) const;
    bool IsTrigger(int button) const;

    int GetNowFrameInput() const { return nowFrameInput; }
    int GetNowFrameNewInput() const { return nowFrameNewInput; }

    // スティック
    bool GetIsMoveLStick() const { return isMoveLStick; }
    bool GetIsMoveRStick() const { return isMoveRStick; }

    float GetLeftStickX() const { return leftStickX; }
    float GetLeftStickY() const { return leftStickY; }

    float GetRightStickX() const { return rightStickX; }
    float GetRightStickY() const { return rightStickY; }

    float GetRightStickPower() const { return rightStickPower; }
    float GetLeftStickPower() const { return leftStickPower; }
private:
    static constexpr float DEADZONE = 0.15f;     // スティックを倒してもすぐ反応しない領域

    XINPUT_STATE nowState{};
    XINPUT_STATE oldState{};

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

    float leftTrigger = 0.0f;           // Lトリガー
    float rightTrigger = 0.0f;          // Rトリガー

    void CalcStickInput();
    void UpdateStick();
};
#pragma once
class Time
{
private:
	// コンストラクタを非公開にする
	Time() {}

	// コピーコンストラクタと代入演算子を削除
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	~Time() {}

public:
	// インスタンスを取得
	static Time& GetInstance()
	{
		static Time instance;
		return instance;
	}

	void Update();

	float GetDeltaTime() const { return deltaTime; }
	float GetScaledDeltaTime() const { return scaledDeltaTime; }
	const float GetTimeScale() { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

private:
	long long prevTime = 0;
	float deltaTime = 0.0f;			// 実時間
	float scaledDeltaTime = 0.0f;	// スロー適用後
	float timeScale = 1.0f;			// タイムスケール
};
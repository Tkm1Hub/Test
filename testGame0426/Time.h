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
	const float GetWorldTimeScale() { return worldTimeScale; }
	void SetWorldTimeScale(float scale) { worldTimeScale = scale; }
	const float GetPlayerTimeScale() { return playerTimeScale; }
	void SetPlayerTimeScale(float scale) { playerTimeScale = scale; }
	void StartHitStop(float time) { hitStopTimer = time; }

	bool IsHitStop() const { return hitStopTimer > 0.0f; }
private:
	long long prevTime = 0;
	float deltaTime = 0.0f;			// 実時間
	float scaledDeltaTime = 0.0f;	// スロー適用後
	float worldTimeScale = 1.0f;	// 世界のタイムスケール
	float playerTimeScale = 1.0f;	// プレイヤーのタイムスケール
	float hitStopTimer = 0.0f;
};
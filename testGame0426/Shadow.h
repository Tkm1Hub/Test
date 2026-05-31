#pragma once
class Shadow
{
public:
	void Init();
	void Update(const VECTOR& pos);

	int GetShadowMapHandle() const { return shadowMapHandle; }
	VECTOR GetLightDir()const { return lightDirection; }

private:
	int shadowMapHandle = -1;					// 影のモデルハンドル

	VECTOR lightDirection = { 0.0f,0.0f,0.0f };	// 光の方向ベクトル

	static constexpr int SHADOW_QUALITY = 2048;	// 影のクオリティ

	float drawShadowRadius = 1000.0f;			// 影を描画する範囲の半径
	float drawShadowHeight = 300.0f;				// 影を描画する範囲の高さ
};
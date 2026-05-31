#include "stdafx.h"
#include "Shadow.h"

void Shadow::Init()
{
	shadowMapHandle = MakeShadowMap(SHADOW_QUALITY, SHADOW_QUALITY);
	lightDirection = VGet(0.1f, -1.0f, -0.1f);

	// ライトの方向を設定
	SetLightDirection(lightDirection);

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(shadowMapHandle, lightDirection);
}

void Shadow::Update(const VECTOR& pos)
{

	//シャドウを描画する範囲を指定
	VECTOR minPos = VSub(pos, VGet(drawShadowRadius, drawShadowHeight, drawShadowRadius));
	VECTOR maxPos = VAdd(pos, VGet(drawShadowRadius, drawShadowHeight, drawShadowRadius));

	SetShadowMapDrawArea(shadowMapHandle, minPos, maxPos);
}
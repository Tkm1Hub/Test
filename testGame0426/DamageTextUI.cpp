#include "stdafx.h"
#include "DamageTextUI.h"
#include "Time.h"

void DamageTextUI::Init(
	const VECTOR& worldPos,
	int damage
)
{
	screenPos =
		ConvWorldPosToScreenPos(worldPos);

	this->damage = damage;
}

void DamageTextUI::Update()
{
	timer +=
		Time::GetInstance().GetScaledDeltaTime()
		* 60.0f;

	//--------------------------------
	// 上へ移動
	//--------------------------------

	screenPos.y += velocityY;

	//--------------------------------
	// フェードアウト
	//--------------------------------

	float rate =
		1.0f - (timer / lifeTime);

	rate = max(0.0f, min(rate, 1.0f));

	alpha =
		static_cast<int>(255 * rate);

	//--------------------------------
	// 削除
	//--------------------------------

	if (timer >= lifeTime)
	{
		isDestroy = true;
	}
}

void DamageTextUI::Draw()
{
	SetDrawBlendMode(
		DX_BLENDMODE_ALPHA,
		alpha
	);

	DrawFormatString(
		static_cast<int>(screenPos.x),
		static_cast<int>(screenPos.y),
		GetColor(255, 80, 80),
		"%d",
		damage
	);

	SetDrawBlendMode(
		DX_BLENDMODE_NOBLEND,
		0
	);
}
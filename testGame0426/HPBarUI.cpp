#include "stdafx.h"
#include "HPBarUI.h"
#include "DamageableObject.h"

void HPBarUI::SetTarget(std::weak_ptr<DamageableObject> target)
{
	this->target = target;
}

void HPBarUI::Update()
{
	auto t = target.lock();
	if (!t)
	{
		isDestroy = true;
		return;
	}

	// HP割合を取得
	hpRate =
		static_cast<float>(t->GetHP()) /
		static_cast<float>(t->GetMaxHP());

	// 0～1に制限
	hpRate = max(0.0f, min(hpRate, 1.0f));

	// スクリーン座標に変換
	screenPos = ConvWorldPosToScreenPos(t->GetPosition());

}

void HPBarUI::Draw()
{
	int left =
		static_cast<int>(screenPos.x - width * 0.5f);

	int top =
		static_cast<int>(screenPos.y - height * 0.5f);

	int right =
		static_cast<int>(screenPos.x + width * 0.5f);

	int bottom =
		static_cast<int>(screenPos.y + height * 0.5f);

	// ゲージ枠
	DrawBox(
		left,
		top,
		right,
		bottom,
		GetColor(50, 50, 50),
		FALSE
	);

	// ゲージ中身
	DrawBox(
		left,
		top,
		left + static_cast<int>(width * hpRate),
		bottom,
		GetColor(100, 0, 0),
		TRUE
	);
}
#include "stdafx.h"
#include "HPBarUI.h"
#include "DamageableObject.h"
#include "StunComponent.h"

void HPBarUI::SetTarget(
	std::weak_ptr<DamageableObject> target
)
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

	//--------------------------------
	// HP割合
	//--------------------------------

	hpRate =
		static_cast<float>(t->GetHP()) /
		static_cast<float>(t->GetMaxHP());

	hpRate =
		std::max(0.0f, std::min(hpRate, 1.0f));

	//--------------------------------
	// スタン割合
	//--------------------------------

	auto stun =
		dynamic_cast<StunComponent*>(
			t.get()
			);

	if (stun)
	{
		stunRate =
			stun->GetStunGauge() /
			stun->GetMaxStunGauge();

		stunRate =
			std::max(0.0f, std::min(stunRate, 1.0f));
	}

	//--------------------------------
	// スクリーン座標
	//--------------------------------

	screenPos =
		ConvWorldPosToScreenPos(
			t->GetPosition()
		);
}

void HPBarUI::Draw()
{
	int left =
		static_cast<int>(
			screenPos.x - width * 0.5f
			);

	//--------------------------------
	// HPバー
	//--------------------------------

	int hpTop =
		static_cast<int>(
			screenPos.y
			);

	int hpBottom =
		static_cast<int>(
			hpTop + hpHeight
			);

	// 枠
	DrawBox(
		left,
		hpTop,
		left + static_cast<int>(width),
		hpBottom,
		GetColor(50, 50, 50),
		FALSE
	);

	// 中身
	DrawBox(
		left,
		hpTop,
		left + static_cast<int>(width * hpRate),
		hpBottom,
		GetColor(180, 40, 40),
		TRUE
	);

	//--------------------------------
	// スタンバー
	//--------------------------------

	int stunTop =
		hpBottom + 4;

	int stunBottom =
		static_cast<int>(
			stunTop + stunHeight
			);

	// 枠
	DrawBox(
		left,
		stunTop,
		left + static_cast<int>(width),
		stunBottom,
		GetColor(50, 50, 50),
		FALSE
	);

	// 中身
	DrawBox(
		left,
		stunTop,
		left + static_cast<int>(width * stunRate),
		stunBottom,
		GetColor(255, 220, 40),
		TRUE
	);
}
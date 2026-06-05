#include "stdafx.h"
#include "HPBarUI.h"
#include "DamageableObject.h"
#include "StunComponent.h"
#include "CharacterBase.h"

void HPBarUI::SetTarget(
	std::weak_ptr<CharacterBase> target
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

	float currentHpRate =
		static_cast<float>(t->GetHP()) /
		static_cast<float>(t->GetMaxHP());

	currentHpRate =
		std::clamp(currentHpRate, 0.0f, 1.0f);

	// 初回同期
	if (damageHpRate <= 0.0f && currentHpRate > 0.0f)
	{
		damageHpRate = currentHpRate;
	}

	// HP減少
	if (currentHpRate < hpRate)
	{
		damageDelayTimer = 0.0f;
	}

	hpRate = currentHpRate;

	//--------------------------------
	// ダメージバー更新
	//--------------------------------

	if (damageHpRate > hpRate)
	{
		damageDelayTimer += 1.0f;

		if (damageDelayTimer >= DamageDelay)
		{
			damageHpRate +=
				(hpRate - damageHpRate)
				* 0.08f;

			if (damageHpRate < hpRate)
			{
				damageHpRate = hpRate;
			}
		}
	}
	else
	{
		damageHpRate = hpRate;
	}

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
			std::clamp(stunRate, 0.0f, 1.0f);
	}

	//--------------------------------
	// スクリーン座標
	//--------------------------------

	screenPos =
		ConvWorldPosToScreenPos(
			t->GetCapsuleTop()
		);

	screenPos.y -= 80;
}

void HPBarUI::Draw()
{
	//--------------------------------
	// HPバー
	//--------------------------------

	int left =
		static_cast<int>(
			screenPos.x - width * 0.5f
			);

	int hpTop =
		static_cast<int>(
			screenPos.y
			);

	int hpBottom =
		static_cast<int>(
			hpTop + hpHeight
			);

	// 背景
	DrawBox(
		left,
		hpTop,
		left + static_cast<int>(width),
		hpBottom,
		GetColor(30, 30, 30),
		TRUE
	);

	// ダメージバー（遅れて減る）
	DrawBox(
		left,
		hpTop,
		left + static_cast<int>(width * damageHpRate),
		hpBottom,
		GetColor(220, 120, 120),
		TRUE
	);

	// 現在HP
	DrawBox(
		left,
		hpTop,
		left + static_cast<int>(width * hpRate),
		hpBottom,
		GetColor(180, 40, 40),
		TRUE
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
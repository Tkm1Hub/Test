#pragma once
#include "UIBase.h"

class DamageTextUI : public UIBase
{
public:

	void Init(
		const VECTOR& worldPos,
		int damage
	);

	void Update() override;

	void Draw() override;

private:

	int damage = 0;

	float timer = 0.0f;

	float lifeTime = 60.0f;

	float velocityY = -1.0f;

	int alpha = 255;
};
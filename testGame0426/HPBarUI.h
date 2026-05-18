#pragma once
#include "UIBase.h"

class DamageableObject;
class HPBarUI : public UIBase
{
public:
	void SetTarget(std::weak_ptr<DamageableObject> target);
	void Update();
	void Draw();
private:
	std::weak_ptr<DamageableObject> target;

	float width = 200.0f;
	float hpHeight = 10.0f;
	float stunHeight = 6.0f;

	float hpRate = 0.0f;
	float stunRate = 0.0f;
};
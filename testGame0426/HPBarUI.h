#pragma once
#include "UIBase.h"

class CharacterBase;
class HPBarUI : public UIBase
{
public:
	void SetTarget(std::weak_ptr<CharacterBase> target);
	void Update();
	void Draw();
private:
	std::weak_ptr<CharacterBase> target;

	float width = 170.0f;
	float hpHeight = 10.0f;
	float stunHeight = 6.0f;

	// ’x‚ê‚ÄŒ¸‚éƒo[
	float damageHpRate = 1.0f;
	float damageDelayTimer = 0.0f;

	float hpRate = 0.0f;
	float stunRate = 0.0f;

	static constexpr float DamageDelay = 20.0f;
	static constexpr float DamageSpeed = 0.02f;
};
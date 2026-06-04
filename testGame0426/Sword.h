#pragma once
#include "Object.h"

class  Player;
class Sword : public Object
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void SetOwner(std::weak_ptr<Player> player) { owner = player; }

private:
	// “‚Ìƒ{[ƒ“”Ô†
	int bradeStartIndex = -1;
	int bradeEndIndex = -1;

	std::weak_ptr<Player> owner;

};
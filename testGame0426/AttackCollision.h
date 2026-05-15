#pragma once

class CharacterBase;
class AttackHitSphere;

namespace AttackCollision
{
	// AttackHitSphere‚ÆCharacter‚Ì”»’è
	bool CheckHit(
		AttackHitSphere* hitSphere,
		CharacterBase* target
	);

	// UŒ‚ˆ—
	void ProcessHit(
		AttackHitSphere* hitSphere
	);
}
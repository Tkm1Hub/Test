#pragma once

class Object;
class AttackHitSphere;

namespace AttackCollision
{
	// AttackHitSphere‚ÆObject‚Ì”»’è
	bool CheckHit(
		AttackHitSphere* hitSphere,
		Object* target
	);

	// UŒ‚ˆ—
	void ProcessHit(
		AttackHitSphere* hitSphere
	);
}
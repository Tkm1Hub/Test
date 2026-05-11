#include "Object.h"

void Object::ApplyGravity()
{
	if (isGround) return;

	verticalVelocity -= GRAVITY;
	
	// ‘¬“x‚ª‘‚­‚È‚è‚·‚¬‚È‚¢‚æ‚¤‚É§ŒÀ
	if (verticalVelocity < -1.0f)
	{
		verticalVelocity = -1.0;
	}

}
#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerDodgeState.h"

void PlayerDodgeState::OnStart()
{
	// Œ»Ý‚Ì“ü—Í•ûŒü‚ðŽæ“¾
	VECTOR dodgeDir = GetPlayer()->GetInputDir();

	// “ü—Í•ûŒü‚É‰ñ”ð‘¬“x‚ð‰ÁŽZ
	GetPlayer()->SetExternalVelocity(
		VScale(dodgeDir, GetPlayer()->GetParam().dodgeSpeed));
}

void PlayerDodgeState::OnUpdate()
{

}

void PlayerDodgeState::OnExit()
{

}
#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerSPAttackState.h"
#include "PlayerDodgeState.h"
#include "PlayerBlockState.h"
#include "Time.h"
#include "EffectContainer.h"
#include "Enemy.h"

void PlayerSPAttackState::OnStart()
{
	auto player = GetPlayer();
	if (!player)return;

	auto target = player->GetTarget().lock();
	if (!target)return;

	VECTOR targetDir = VSub(
		target->GetPosition(),
		player->GetPosition()
	);

	targetDir.y = 0.0f;

	targetDir = VNorm(targetDir);

	// 正面を合わせる
	player->SetLookDir(targetDir);
}

void PlayerSPAttackState::OnUpdate()
{
	// player取得
	auto player = GetPlayer();
	if (!player) return;

	// タイマー
	timer += Time::GetInstance().GetScaledDeltaTime() * 60;

	// 攻撃データ取得
	const AttackData& SPAttackData = player->GetSPAttackData();

	// 現在段
	const AttackStep& step = SPAttackData.combo[currentStep];

	//--------------------------------
	// 次コンボ入力受付
	//--------------------------------

	switch (phase)
	{
		// ===== 準備 =====
	case AttackPhase::Windup:

		PlayAttackAnimation(currentStep);

		if (timer >= step.windupTime)
		{
			timer = 0.0f;

			phase = AttackPhase::Active;
		}

		break;

		// ===== 攻撃 =====
	case AttackPhase::Active:

		if (!hasHit)
		{
			player->Attack(step);
			hasHit = true;
		}
		if (timer >= step.activeTime)
		{
			timer = 0.0f;
			phase = AttackPhase::Recovery;
		}
		break;

		// ===== 後隙 =====
	case AttackPhase::Recovery:


		if (timer >= step.recoveryTime)
		{
			timer = 0.0f;

			//--------------------------------
			// 次コンボへ
			//--------------------------------

			if (currentStep + 1 < SPAttackData.combo.size())
			{
				currentStep++;

				phase = AttackPhase::Windup;

				hasHit = false;

				nextComboRequested = false;

				return;
			}

			//--------------------------------
			// コンボ終了
			//--------------------------------

			if (Input::GetInput().GetIsMoveLStick())
			{
				auto state =
					std::make_shared<PlayerWalkState>();

				player->ChangeState(state);
			}
			else
			{
				auto state =
					std::make_shared<PlayerIdleState>();

				player->ChangeState(state);
			}

			return;
		}
		break;
	}

}

void PlayerSPAttackState::OnExit()
{

}

void PlayerSPAttackState::PlayAttackAnimation(int step)
{
	switch (step)
	{
	case 0:
		GetPlayer()->PlayAnimation((int)(PlayerAnimState::SPAttack1), false);
		break;
	case 1:
		GetPlayer()->PlayAnimation((int)(PlayerAnimState::SPAttack2), false);
		break;
	}
}
#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerAttackState.h"
#include "PlayerDodgeState.h"
#include "PlayerBlockState.h"
#include "Time.h"
#include "EffectContainer.h"
#include "Enemy.h"

void PlayerAttackState::OnStart()
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

void PlayerAttackState::OnUpdate()
{
	// player取得
	auto player = GetPlayer();
	if (!player) return;

	// タイマー
	timer += Time::GetInstance().GetScaledDeltaTime() * 60;

	// 攻撃データ取得
	const AttackData& attackData = player->GetAttackData();

	// 現在段
	const AttackStep& step = attackData.combo[currentStep];

	//--------------------------------
	// 次コンボ入力受付
	//--------------------------------

	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_X))
	{
		nextComboRequested = true;
	}

	// 回避
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		auto state = std::make_shared<PlayerDodgeState>();
		player->ChangeState(state);
		return;
	}

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

		// Lボタンでガード
		if (Input::GetInput().IsPress(XINPUT_BUTTON_LEFT_SHOULDER))
		{
			auto state = std::make_shared<PlayerBlockState>();
			GetPlayer()->ChangeState(state);
			return;
		}


		//--------------------------------
		// 次コンボへ
		//--------------------------------

		if (nextComboRequested &&
			currentStep + 1 < attackData.combo.size())
		{
			currentStep++;

			phase = AttackPhase::Windup;

			hasHit = false;

			nextComboRequested = false;

			return;
		}

		if (timer >= step.recoveryTime)
		{
			timer = 0.0f;


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

void PlayerAttackState::OnExit()
{

}

void PlayerAttackState::PlayAttackAnimation(int step)
{
	switch (step)
	{
	case 0:
		GetPlayer()->PlayAnimation((int)(PlayerAnimState::Slash1), false);
		break;
	case 1:
		GetPlayer()->PlayAnimation((int)(PlayerAnimState::Slash2), false);
		break;
	case 2:
		GetPlayer()->PlayAnimation((int)(PlayerAnimState::Slash3), false);
		break;
	case 3:
		GetPlayer()->PlayAnimation((int)(PlayerAnimState::Slash4), false);
		break;
	case 4:
		GetPlayer()->PlayAnimation((int)(PlayerAnimState::Slash5), false);
		break;
	}
}
#pragma once
#include "DamageableObject.h"
#include "StateMachine.h"
#include "AttackData.h"

enum class Team
{
	Neutral,
	Player,
	Enemy
};

class CharacterBase :
    public DamageableObject
{
public:
	//カプセル
	VECTOR GetCapsuleBottom() const;
	VECTOR GetCapsuleTop() const;
	VECTOR GetCapsuleCenter() const;
	float GetBodyRadius() const { return bodyRadius; }
	float GetBodyHeight() const { return bodyHeight; }

	// ステート名取得
	const char* GetStateName() const
	{
		auto state = stateMachine.GetCurrentState();

		if (!state)
			return "None";

		return state->GetName();
	}

	// チーム取得
	Team GetTeam() const
	{
		return team;
	}

	// コンボ設定
	virtual void SetupCombo(
		const std::vector<AttackStep>& comboData
	);

	const AttackData& GetAttackData() const
	{
		return attackData;
	}

protected:
	Team team = Team::Neutral;

    float bodyRadius = 0.0f;	// 当たり判定半径
	float bodyHeight = 0.0f;	// 当たり判定高さ

	AttackData attackData;
};
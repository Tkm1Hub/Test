#include "stdafx.h"
#include "Debug.h"
#include "Input.h"
#include "Time.h"
#include "Objects.h"
#include "Object.h"
#include "CharacterBase.h"
#include "Player.h"
#include "Enemy.h"

void Debug::Update()
{

	if (CheckHitKey(KEY_INPUT_UP))
	{
		float timeScale = Time::GetInstance().GetTimeScale();
		timeScale += 0.01f;
		Time::GetInstance().SetTimeScale(timeScale);
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		float timeScale = Time::GetInstance().GetTimeScale();
		timeScale -= 0.01f;
		Time::GetInstance().SetTimeScale(timeScale);
	}

}

void Debug::Draw()
{
	// 地面グリッド
	DrawGridLine(50.0f, 1000.0f);

	// 入力表示
	DrawInputDebug();

	DrawObjectInfo();

	// ターゲットマーカー描画
	DrawTargetMarker();

	DrawCharacterCollision();

	// プレイヤー索敵範囲描画
	for (auto& obj : Objects::GetInstance().objects)
	{
		auto player =
			std::dynamic_pointer_cast<Player>(obj);

		if (!player)
			continue;

		DrawCylinder(
			player->GetPosition(),
			player->GetParam().SearchEnemyDistance,
			0.2f,
			24,
			GetColor(0, 180, 255)
		);

		DrawCapsule3D(
			player->GetCapsuleBottom(),
			player->GetCapsuleTop(),
			player->GetBodyRadius(),
			8,
			GetColor(0, 180, 255),
			GetColor(0, 0, 0),
			FALSE
		);

	// キャラクターステート描画
	DrawCharacterState();

	}

}

//
// 入力デバッグ表示
//
void Debug::DrawInputDebug()
{
	printfDx("LeftStickX : %.2f \n",
		Input::GetInput().GetLeftStickX());

	printfDx("LeftStickY : %.2f \n",
		Input::GetInput().GetLeftStickY());

	printfDx("LeftStickPower : %.2f \n",
		Input::GetInput().GetLeftStickPower());

	printfDx("LeftTriggerPower : %.2f \n",
		Input::GetInput().GetLeftTrigger());

	printfDx("nowFrameInput : %i \n",
		Input::GetInput().GetNowFrameInput());

	printfDx("TimeScale : %.1f \n",
		Time::GetInstance().GetTimeScale());
}

//
// ステート名表示
//
void Debug::DrawCharacterState()
{
	for (auto& obj : Objects::GetInstance().objects)
	{
		auto character =
			dynamic_cast<CharacterBase*>(obj.get());

		if (!character)
			continue;

		VECTOR worldPos =
			VAdd(
				character->GetCapsuleTop(),
				VGet(0.0f, 5.0f, 0.0f)
			);

		VECTOR screenPos =
			ConvWorldPosToScreenPos(worldPos);

		DrawString(
			static_cast<int>(screenPos.x),
			static_cast<int>(screenPos.y),
			character->GetStateName(),
			GetColor(255, 255, 0)
		);
	}
}

//
// ターゲット表示
//
void Debug::DrawTargetMarker()
{
	for (auto& obj : Objects::GetInstance().objects)
	{
		auto player =
			std::dynamic_pointer_cast<Player>(obj);

		if (!player)
			continue;

		//--------------------------------
		// ロックオン中
		//--------------------------------

		if (player->GetIsLockOn())
		{
			auto lockOnTarget =
				player->GetTarget().lock();

			if (!lockOnTarget)
				continue;

			VECTOR worldPos =
				lockOnTarget->GetCapsuleTop();

			VECTOR screenPos =
				ConvWorldPosToScreenPos(worldPos);

			// ロックオン専用表示
			DrawString(
				(int)screenPos.x,
				(int)screenPos.y - 60,
				"LOCK ON",
				GetColor(255, 0, 0)
			);

			DrawCircle(
				(int)screenPos.x,
				(int)screenPos.y,
				28,
				GetColor(255, 0, 0),
				FALSE
			);

			continue;
		}

		//--------------------------------
		// 通常ターゲット
		//--------------------------------

		auto target =
			player->GetTarget().lock();

		if (!target)
			continue;

		VECTOR worldPos =
			target->GetCapsuleTop();

		VECTOR screenPos =
			ConvWorldPosToScreenPos(worldPos);

		DrawString(
			(int)screenPos.x,
			(int)screenPos.y - 50,
			"▼ TARGET",
			GetColor(180, 180, 0)
		);

		DrawCircle(
			(int)screenPos.x,
			(int)screenPos.y,
			20,
			GetColor(180, 180, 0),
			FALSE
		);
	}
}
//
// グリッド描画
//
void Debug::DrawGridLine(
	float interval,
	float diameter
)
{
	int lineCount =
		static_cast<int>(diameter / interval);

	float half =
		lineCount * interval;

	// Z方向
	for (int i = -lineCount; i <= lineCount; i++)
	{
		float x = i * interval;

		VECTOR start =
			VGet(x, 0.0f, -half);

		VECTOR end =
			VGet(x, 0.0f, half);

		DrawLine3D(
			start,
			end,
			GetColor(50, 50, 50)
		);
	}

	// X方向
	for (int i = -lineCount; i <= lineCount; i++)
	{
		float z = i * interval;

		VECTOR start =
			VGet(-half, 0.0f, z);

		VECTOR end =
			VGet(half, 0.0f, z);

		DrawLine3D(
			start,
			end,
			GetColor(50, 50, 50)
		);
	}
}

//
// 円柱描画
//

// 円柱の描画
void Debug::DrawCylinder(VECTOR pos, float radius, float height, float division, unsigned int color)
{
	float yTop = pos.y + height / 2.0f;
	float yBottom = pos.y - height / 2.0f;

	// 頂点を計算して線を描画
	for (int i = 0; i < division; i++)
	{
		float angle1 = 2.0f * DX_PI_F * i / division;
		float angle2 = 2.0f * DX_PI_F * (i + 1) / division;

		VECTOR top1 = VGet(pos.x + cosf(angle1) * radius, yTop, pos.z + sinf(angle1) * radius);
		VECTOR top2 = VGet(pos.x + cosf(angle2) * radius, yTop, pos.z + sinf(angle2) * radius);
		VECTOR bottom1 = VGet(pos.x + cosf(angle1) * radius, yBottom, pos.z + sinf(angle1) * radius);
		VECTOR bottom2 = VGet(pos.x + cosf(angle2) * radius, yBottom, pos.z + sinf(angle2) * radius);

		// 側面の線
		DrawLine3D(top1, bottom1, color);
		DrawLine3D(top2, bottom2, color);

		// 上面の線
		DrawLine3D(top1, top2, color);

		// 下面の線
		DrawLine3D(bottom1, bottom2, color);
	}
}

void Debug::DrawObjectInfo()
{
	for (auto& obj : Objects::GetInstance().objects)
	{
		if (!obj)
			continue;

		//--------------------------------
		// Forward
		//--------------------------------

		DrawLine3D(
			VAdd(obj->GetPosition(), VGet(0.0f, 2.5f, 0.0f)),
			VAdd(
				VAdd(obj->GetPosition(), VGet(0.0f, 2.5f, 0.0f)),
				VScale(obj->GetForward(), 50.0f)
			),
			GetColor(255, 0, 0)
		);

		//--------------------------------
		// MoveDir
		//--------------------------------

		DrawLine3D(
			VAdd(obj->GetPosition(), VGet(0.0f, 2.0f, 0.0f)),
			VAdd(
				VAdd(obj->GetPosition(), VGet(0.0f, 2.0f, 0.0f)),
				VScale(obj->GetMoveDir(), 40.0f)
			),
			GetColor(0, 255, 0)
		);

		//--------------------------------
		// Velocity
		//--------------------------------

		DrawLine3D(
			obj->GetPosition(),
			VAdd(
				obj->GetPosition(),
				VScale(obj->GetMoveVelocity(), 30.0f)
			),
			GetColor(0, 0, 255)
		);
	}
}

void Debug::DrawCharacterCollision()
{
	for (auto& obj : Objects::GetInstance().objects)
	{
		auto character =
			dynamic_cast<CharacterBase*>(obj.get());

		if (!character)
			continue;

		DrawCapsule3D(
			character->GetCapsuleBottom(),
			character->GetCapsuleTop(),
			character->GetBodyRadius(),
			8,
			GetColor(0, 180, 255),
			GetColor(0, 0, 0),
			FALSE
		);
	}
}
#include "stdafx.h"
#include "Debug.h"
#include "Input.h"
#include "Time.h"
#include "Objects.h"
#include "Object.h"
#include "CharacterBase.h"

void Debug::Update()
{
}

void Debug::Draw()
{
	clsDx();

	printfDx("LeftStickX : %.0f \n", Input::GetInput().GetLeftStickX());
	printfDx("LeftStickY : %.0f \n", Input::GetInput().GetLeftStickY());
	printfDx("LeftStickPower : %.0f \n", Input::GetInput().GetLeftStickPower());
	printfDx("nowFrameInput : %i \n", Input::GetInput().GetNowFrameInput());
	printfDx("TimeScale : %.1f \n", Time::GetInstance().GetTimeScale());

	for (auto& obj : Objects::GetInstance().objects)
	{
		// キャラクターか確認
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

	DrawGridLine(50.0f, 1000.0f);
}

void Debug:: DrawGridLine(float interval, float diameter)
{
	int lineCount = (int)(diameter / interval);

	// 中心を基準にする
	float half = lineCount * interval;

	// Z方向の線
	for (int i = -lineCount; i <= lineCount; i++)
	{
		float x = i * interval;

		VECTOR start = VGet(x, 0.0f, -half);
		VECTOR end = VGet(x, 0.0f, half);

		DrawLine3D(start, end,GetColor(255, 255, 255));
	}

	// X方向の線
	for (int i = -lineCount; i <= lineCount; i++)
	{
		float z = i * interval;

		VECTOR start = VGet(-half, 0.0f, z);
		VECTOR end = VGet(half, 0.0f, z);

		DrawLine3D(start, end, GetColor(255, 255, 255));
	}
}

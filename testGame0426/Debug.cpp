#include "stdafx.h"
#include "Debug.h"
#include "Input.h"
#include "Time.h"

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

	DrawGridLine(10.0f, 200.0f);
}

void Debug:: DrawGridLine(float interval, float diameter)
{
	int lineCount = (int)(diameter / interval);

	// ’†S‚ğŠî€‚É‚·‚é
	float half = lineCount * interval;

	// Z•ûŒü‚Ìü
	for (int i = -lineCount; i <= lineCount; i++)
	{
		float x = i * interval;

		VECTOR start = VGet(x, 0.0f, -half);
		VECTOR end = VGet(x, 0.0f, half);

		DrawLine3D(start, end,GetColor(255, 255, 255));
	}

	// X•ûŒü‚Ìü
	for (int i = -lineCount; i <= lineCount; i++)
	{
		float z = i * interval;

		VECTOR start = VGet(-half, 0.0f, z);
		VECTOR end = VGet(half, 0.0f, z);

		DrawLine3D(start, end, GetColor(255, 255, 255));
	}
}

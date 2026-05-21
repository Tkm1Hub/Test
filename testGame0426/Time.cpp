#include "stdafx.h"
#include "Time.h"

void Time::Update()
{
    unsigned int now = GetNowCount(); // ƒ~ƒŠ•b
    if (prevTime == 0) prevTime = now;

    double realDelta = (now - prevTime) / 1000.0; // •b‚É•ÏŠ·
    prevTime = now;

    if (realDelta > 0.03) realDelta = 0.03;
    if (realDelta < 0.000001) realDelta = 0.000001;

    deltaTime = realDelta;

    if (hitStopTimer > 0.0f)
    {
        hitStopTimer -= deltaTime;

        scaledDeltaTime = 0.0f;

        return;
    }

    scaledDeltaTime = deltaTime * timeScale;
}
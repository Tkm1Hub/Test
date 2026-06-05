#pragma once

class Debug
{
public:
	void Update();
	void Draw();

private:
	void DrawInputDebug();
	void DrawCharacterState();
	void DrawTargetMarker();
	void DrawGridLine(float interval, float diameter);
	void DrawCylinder(VECTOR pos, float radius, float height, float division, unsigned int color);
	void DrawObjectInfo();
	void DrawCharacterCollision();

	bool prevF1 = false;
	bool isDebugMode = false;
};